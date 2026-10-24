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

from kaitai.data.data_utils import DataMigrationRequest, run_data_migration

@dataclass
class MigrateArgs:
    project: str
    name: str
    output_path: Path

def migrate_data(args: MigrateArgs):
    project = args.project
    name    = args.name

    with open(args.output_path, "w") as stream:
        request = DataMigrationRequest(project=project, name=name, stream=stream)
        run_data_migration(request)
