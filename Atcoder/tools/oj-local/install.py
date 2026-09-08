"""Reapply the local prepare subcommand after reinstalling oj."""
from pathlib import Path
import shutil
import onlinejudge_command

package = Path(onlinejudge_command.__file__).parent
main = package / 'main.py'
source = main.read_text()
marker = 'import onlinejudge_command.subcommand.prepare as subcommand_prepare'
if marker not in source:
    edits = [
        ('import onlinejudge_command.subcommand.download as subcommand_download',
         'import onlinejudge_command.subcommand.download as subcommand_download\n' + marker),
        ('    subcommand_download.add_subparser(subparsers)',
         '    subcommand_prepare.add_subparser(subparsers)\n    subcommand_download.add_subparser(subparsers)'),
        ("    if args.subcommand in ['download', 'd', 'dl']:",
         "    if args.subcommand == 'prepare':\n        return 0 if subcommand_prepare.run(args) else 1\n    if args.subcommand in ['download', 'd', 'dl']:")]
    for old, new in edits:
        if source.count(old) != 1:
            raise SystemExit('oj source changed; patch was not applied')
        source = source.replace(old, new, 1)
    compile(source, str(main), 'exec')
    backup = main.with_suffix('.py.before-prepare')
    if not backup.exists():
        shutil.copy2(main, backup)
    main.write_text(source)
shutil.copy2(Path(__file__).with_name('prepare.py'), package / 'subcommand/prepare.py')
print('Installed local oj prepare subcommand')
