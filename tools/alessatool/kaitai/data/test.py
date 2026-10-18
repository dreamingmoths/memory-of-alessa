from dataclasses import dataclass
import sys
from traceback import print_exception
from posixpath import abspath

sys.path.append(abspath("tools/alessatool"))

from kaitai.data.config import PROJECT_DATA_CONFIG, SH2_DATA, SH3_DATA
from kaitai.data.data_utils import DataMigrationRequest, run_data_migration

@dataclass
class TestResult:
    name: str
    passing: int = 0
    count: int = 0
    skip: bool = False

def run_tests():
    results: list[TestResult] = []
    for name in PROJECT_DATA_CONFIG:
        result = run_project_test(name)
        results.append(result)

    for result in results:
        name = result.name

        if result.skip:
            print(f"🟠 {name} skipped ({result.count} tests)")
            continue

        passing = result.passing
        count = result.count
        failing = count - passing
        success = passing == count
        emoji = success and "🟣" or "🔴"
        if success: text = f"all {count} tests passing"
        else: text = f"{passing} passing, {failing} failing"
        print(f"{emoji} {bold(name)}: {text}")

def run_project_test(name: str) -> TestResult:
    data_config = PROJECT_DATA_CONFIG[name]
    table = data_config.table
    if len(table) == 0:
        return TestResult(name=name, skip=True)

    passing = count = 0
    for data in table:
        count += 1
        print(bold(f"test: {data.name}"))
        try:
            run_data_migration(DataMigrationRequest(name, data.name, "/dev/null"))
            passing += 1
        except Exception as exception:
            print(f"🔴 test failed for {data.name}")
            print_exception(exception)

    return TestResult(name=name, passing=passing, count=count)

def bold(text: str):
    return '\033[1m' + text + '\033[0m'

if __name__ == "__main__":
    run_tests()
