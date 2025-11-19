import os
import subprocess
from pathlib import Path

def normalize_lines(content):
    lines = [line.rstrip() for line in content.splitlines()]
    while lines and not lines[-1]:
        lines.pop()
    return lines

def compare_files(c_file, res_file):
    try:
        with open(c_file, 'r') as f1, open(res_file, 'r') as f2:
            c_content = normalize_lines(f1.read())
            res_content = normalize_lines(f2.read())
            return c_content == res_content
    except FileNotFoundError:
        return False
    
def generate_output():
    test_dir = Path("./test/resources")
    if not test_dir.exists():
        return False, "Test directory not found."
    
    interpreter = Path("./build/interpreter")
    if not interpreter.exists():
        return False, "Interpreter not found. Please build the project first."
    
    try:
        for input_file in test_dir.glob("*.in"):
            base_name = input_file.stem
            outfile = test_dir / f"{base_name}.out"

            with open(outfile, 'w') as out_file:
                subprocess.run(["./build/interpreter", input_file], stdout=out_file)
                print(f"Generated interpreter output: {outfile}")
        return True, "Output generated successfully."
    except Exception as e:
        return False, str(e)
    
def main():
    success, message = generate_output()
    if not success:
        print(message)
        return
    print(message)
    
    total_tests = 0
    passed_tests = 0

    test_dir = Path("./test/resources")
    
    # 打印表头
    print("\n╔══════════════════════════════╗")
    print("║        TEST RESULTS          ║")
    print("╠════════════════╦═════════════╣")
    print("║ Test Name      ║ Result      ║")
    print("╠════════════════╬═════════════╣")

    for ans_file in test_dir.glob("*.ans"):
        total_tests += 1
        base_name = ans_file.stem
        out_file = test_dir / f"{base_name}.out"
        
        if compare_files(ans_file, out_file):
            passed_tests += 1
            print(f"║ {base_name.ljust(14)} ║ \033[32m✓ Passed\033[0m    ║")  # 绿色
        else:
            print(f"║ {base_name.ljust(14)} ║ \033[31m✗ Failed\033[0m    ║")  # 红色

    # 打印表尾和统计信息
    print("╚════════════════╩═════════════╝")
    print("\n📊 Test Summary:")
    print(f"   Total tests:  {total_tests}")
    print(f"   Passed tests: \033[32m{passed_tests}\033[0m")
    print(f"   Failed tests: \033[31m{total_tests - passed_tests}\033[0m")
    
    if passed_tests == total_tests:
        print("\n\033[32m🎉 All tests passed!\033[0m")
    else:
        print("\n\033[31m⚠️  Some tests failed!\033[0m")

if __name__ == "__main__":
    main()