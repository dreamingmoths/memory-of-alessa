import sys
from pathlib import Path
from posixpath import abspath
from dataclasses import dataclass
from traceback import print_exception

sys.path.append(abspath("tools/alessatool"))

from kaitai.data.config import PROJECT_DATA_CONFIG
from kaitai.data.data_utils import AlessastructDataOptions, DataMigrationRequest, run_data_migration

@dataclass
class TestResult:
    name: str
    passing: int = 0
    count: int = 0
    skip: bool = False

def run_tests():
    configure()

    results: list[TestResult] = []
    for name in PROJECT_DATA_CONFIG:
        result = run_project_test(name)
        results.append(result)

    for result in results:
        name = result.name

        if result.skip:
            print(f"🟠 {bold(name)}: skipped ({result.count} tests)")
            continue

        passing = result.passing
        count = result.count
        failing = count - passing
        success = passing == count
        emoji = success and "🟣" or "🔴"
        if success: text = f"all {count} tests passing"
        else: text = f"{passing} passing, {failing} failing"
        print(f"{emoji} {bold(name)}: {text}")

def run_project_test(project: str) -> TestResult:
    data_config = PROJECT_DATA_CONFIG[project]
    table = data_config.table
    if len(table) == 0:
        return TestResult(name=project, skip=True)

    passing = count = 0
    for data in table:
        count += 1
        print(bold(f"test: {data.name}"))
        try:
            request = DataMigrationRequest(
                project=project,
                name=data.name,
                output_path=Path("/dev/null")
            )
            run_data_migration(request)
            passing += 1
        except Exception as exception:
            print(f"🔴 test failed for {data.name}")
            print_exception(exception)

    return TestResult(name=project, passing=passing, count=count)

def configure():
    AlessastructDataOptions.SILENCE_DEV_WARNINGS = True

def bold(text: str):
    return '\033[1m' + text + '\033[0m'

if __name__ == "__main__":
    run_tests()
