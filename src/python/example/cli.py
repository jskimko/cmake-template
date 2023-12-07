__all__ = [
  'CLIParser',
]

import argparse
from ._example import log, Settings

class CLIParser(argparse.ArgumentParser):
  def __init__(self, *args, **kwargs):

    if 'formatter_class' in kwargs:
      formatter_class = kwargs['formatter_class']
    else:
      kwargs['formatter_class'] = \
        lambda prog: argparse.ArgumentDefaultsHelpFormatter(prog, max_help_position=80)

    super().__init__(*args, **kwargs)

    self.add_argument('-v', '--verbosity', type=log_Level_type, default=log.INFO,
                      help='default verbosity level')

  def parse_args(self, *args, **kwargs):
    args = super().parse_args(*args, **kwargs)

    Settings.setInt('verbosity', args.verbosity)

    return args

def log_Level_type(s):
  if s in log.Level.__members__:
    return eval(f'log.Level.{s}')
  else:
    return log.Level(int(s))
