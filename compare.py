import math

def compare_files(file1, file2, tolerance=0.001):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        lines1 = f1.readlines()
        lines2 = f2.readlines()

        if len(lines1) != len(lines2):
            print("Files have different number of lines.")
            return

        for idx, (line1, line2) in enumerate(zip(lines1, lines2)):
            x = float(line1.strip())
            y = float(line2.strip())
            if math.fabs(x - y) > tolerance:
                print(f"Difference at index {idx}: {x} vs {y}")

if __name__ == "__main__":
    compare_files('OUTPUT.txt', 'OUTPUT2.txt')