import random
from array import array
from pathlib import Path

N = 1_000_000
OUT = Path("random_dataset")
OUT.mkdir(exist_ok=True)

# Cố định seed để tái tạo kết quả; bỏ dòng này nếu muốn ngẫu nhiên hoàn toàn
random.seed(2024)

for idx in range(1, 11):
    # Sinh N số thực ngẫu nhiên trong [0, 1)
    arr = array("d", (random.random() for _ in range(N)))

    if idx == 1:
        # Dãy 1: tăng dần
        arr = array("d", sorted(arr))
    elif idx == 2:
        # Dãy 2: giảm dần
        arr = array("d", sorted(arr, reverse=True))
    # idx 3..10: giữ nguyên thứ tự ngẫu nhiên

    path = OUT / f"sequence_{idx:02d}.txt"

    # Ghi ra file text, mỗi dòng 1 số
    with open(path, "w", buffering=1 << 20) as f:  # buffer 1MB cho nhanh
        f.write("\n".join(f"{x:.8f}" for x in arr))

    mn, mx = min(arr), max(arr)
    print(f"Đã lưu {path} | {len(arr):,} số | min={mn:.4f}, max={mx:.4f}")

print("Hoàn tất.")