
'''
alessatool/migrate:

migrate data by symbol name. results are written to `out.c` and may require
post-processing.

see `kaitai/data/config.py` for more information.

example:

alessatool migrate --project=silent-hill-2 --name=_pObject_Class_List
'''

from dataclasses import dataclass

from kaitai.data.data_utils import DataMigrationRequest, run_data_migration

@dataclass
class MigrateArgs(DataMigrationRequest):
    pass

def migrate_data(args: MigrateArgs):
    run_data_migration(args)
