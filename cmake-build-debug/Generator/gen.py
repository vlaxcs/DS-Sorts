import os
output_file_path = os.path.dirname(__file__)

test = [
    # INT
    {"count": 1_000, "lower": 0, "upper": 1},
    {"count": 4_000_000, "lower": 0, "upper": 1},
    {"count": 4_000_000, "lower": 0, "upper": 1, "order": "asc"},
    {"count": 4_000_000, "lower": 0, "upper": 1, "order": "desc"},
    {"count": 1_000, "lower": 0, "upper": 10_000},
    {"count": 1_000, "lower": 0, "upper": 2_147_483_647},
    {"count": 1_000_000, "lower": 0, "upper": 2_147_483_647},
    {"count": 4_000_000, "lower": 0, "upper": 2_147_483_647},
    # ULL
    {"count": 1_000, "lower": 0, "upper": 18_446_744_073_709_551_615},
    {"count": 100_000, "lower": 0, "upper": 18_446_744_073_709_551_615},
    {"count": 1_000_000, "lower": 0, "upper": 18_446_744_073_709_551_615},
    {"count": 4_000_000, "lower": 0, "upper": 18_446_744_073_709_551_615},
    # FLOAT
    {"count": 1_000, "lower": -1_000, "upper": 1_000},
    {"count": 100_000, "lower": -1_000, "upper": 1_000},
    {"count": 500_000, "lower": -100_000, "upper": 100_000},
    {"count": 4_000_000, "lower": 0, "upper": 340_282_000_000_000_000_000_000_000_000_000_000}
]

import random
def genTest(file_path: str, test_number: int, type: str, count: int, lower: int, upper: int, order = None):
    output_file_name = file_path + f"/{type.upper()}/{test_number if test_number > 9 else "0" + str(test_number)}" + ".in"
    
    if (type == "int" or type == "ull" or test_number <= 12):
        result = [random.randint(lower, upper) for i in range(0, count)]
    else:
        result = [random.uniform(lower, upper) for i in range(0, count)]

    if (order == "asc"):
        result = sorted(result)
    if (order == "desc"):
        result = sorted(result, reverse=True)

    with open(output_file_name, "w") as f:
        for x in result:
            f.write(f"{x} ")

    print(f"Test {test_number}: Written in {output_file_name}")        

def main():
    for i in range(0, 8):
        if ("order" not in test[i]):
            genTest(output_file_path, i + 1, "int", test[i]["count"], test[i]["lower"], test[i]["upper"])
        else:
            genTest(output_file_path, i + 1, "int", test[i]["count"], test[i]["lower"], test[i]["upper"], test[i]["order"])

    for i in range(0, 12):
        if ("order" not in test[i]):
            genTest(output_file_path, i + 1, "ull", test[i]["count"], test[i]["lower"], test[i]["upper"])
        else:
            genTest(output_file_path, i + 1, "ull", test[i]["count"], test[i]["lower"], test[i]["upper"], test[i]["order"])

    for i in range(0, 16):
        if ("order" not in test[i]):
            genTest(output_file_path, i + 1, "float", test[i]["count"], test[i]["lower"], test[i]["upper"])
        else:
            genTest(output_file_path, i + 1, "float", test[i]["count"], test[i]["lower"], test[i]["upper"], test[i]["order"])        

if __name__ == "__main__":
    main()
    exit()