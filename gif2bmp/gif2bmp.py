from PIL import Image, ImageSequence
import os

# 파일 경로
gif_path = "./gif2bmp/real.gif"
output_dir = "./gif2bmp"

# 출력 폴더가 없으면 생성
os.makedirs(output_dir, exist_ok=True)

# GIF 열기
gif = Image.open(gif_path)

# 프레임 저장
frame_paths = []
for i, frame in enumerate(ImageSequence.Iterator(gif)):
    frame_path = os.path.join(output_dir, f"frame_{i:03d}.bmp")
    frame.convert('RGB').save(frame_path, format="BMP")
    frame_paths.append(frame_path)

len(frame_paths), frame_paths[:5]  # 총 프레임 수와 일부 경로 출력
