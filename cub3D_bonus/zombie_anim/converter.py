import requests
import base64
import time
import os

API_KEY = "6666f18147cfcec66f02a541d0a7c419"
base_path = "."
animations = ["attacking", "dying", "hitted", "walking"]

def convert_file_to_xpm(input_path, output_path, anim, index):
    try:
        with open(input_path, "rb") as f:
            encoded_file = base64.b64encode(f.read()).decode("utf-8")

        print(f"🔄 Convertendo {input_path} → {output_path}")

        # Crea il job
        job_resp = requests.post(
            "https://api.convertio.co/convert",
            json={
                "apikey": API_KEY,
                "input": "base64",
                "file": encoded_file,
                "filename": os.path.basename(input_path),
                "outputformat": "xpm"
            }
        )

        if job_resp.status_code != 200:
            print(f"❌ HTTP Error {job_resp.status_code}")
            return

        job_data = job_resp.json()
        if job_data["code"] != 200:
            print(f"❌ API Error: {job_data}")
            return

        job_id = job_data["data"]["id"]

        # Poll fino a completamento
        while True:
            status_resp = requests.get(f"https://api.convertio.co/convert/{job_id}/status")
            status_data = status_resp.json()

            if status_data["data"]["step"] == "finish":
                break
            elif status_data["data"]["step"] == "error":
                print(f"❌ Errore nella conversione di {input_path}")
                return
            time.sleep(1)

        # Scarica il file convertito
        download_url = status_data["data"]["output"]["url"]
        r = requests.get(download_url)
        os.makedirs(os.path.dirname(output_path), exist_ok=True)
        with open(output_path, "wb") as out_f:
            out_f.write(r.content)

        print(f"✅ Salvato: {output_path}")

    except Exception as e:
        print(f"❌ Errore con {input_path}: {e}")

# Cicla ogni cartella
for anim in animations:
    input_folder = os.path.join(base_path, anim)
    output_folder = os.path.join(base_path, f"{anim}_xpm")
    os.makedirs(output_folder, exist_ok=True)

    files = sorted([f for f in os.listdir(input_folder) if f.endswith(".png")])
    for i, filename in enumerate(files):
        input_path = os.path.join(input_folder, filename)
        output_filename = f"Z{anim}{i}.xpm"
        output_path = os.path.join(output_folder, output_filename)

        convert_file_to_xpm(input_path, output_path, anim, i)
