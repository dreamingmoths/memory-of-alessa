'''
alessatool/migrate:

migrate data by symbol name. results are written to `ctx.c` by default and may
require post-processing.

see `kaitai/data/config.py` for more information.

example:

alessatool migrate --project=silent-hill-2 --name=_pObject_Class_List
'''

from dataclasses import dataclass
from pathlib import Path

from kaitai.data.data_utils import DataMigrationRequest, migrate_asm_file, run_data_migration

@dataclass
class BaseMigrateArgs:
    project: str
    output_path: Path

@dataclass
class SymbolMigrateArgs(BaseMigrateArgs):
    name: str

@dataclass
class AsmFileMigrateArgs(BaseMigrateArgs):
    asm_path: Path

type MigrateArgs = SymbolMigrateArgs | AsmFileMigrateArgs

def migrate_data(args: MigrateArgs):
    project = args.project

    if args.name is not None:
        name = args.name

        with open(args.output_path, "w") as stream:
            request = DataMigrationRequest(project, name, stream)
            run_data_migration(request)
    else:
        asm_path = args.asm_path

        with open(args.output_path, "w") as stream:
            stream.write("\n")

        with open(args.output_path, "a") as stream:
            migrate_asm_file(project, asm_path, stream)
