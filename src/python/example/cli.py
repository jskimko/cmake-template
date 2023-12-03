__all__ = [
  'CLIParser',
]

import argparse

class CLIParser(argparse.ArgumentParser):
  def __init__(self, *args, **kwargs):

    if 'formatter_class' in kwargs:
      formatter_class = kwargs['formatter_class']
    else:
      kwargs['formatter_class'] = \
        lambda prog: argparse.ArgumentDefaultsHelpFormatter(prog, max_help_position=80)

    super().__init__(*args, **kwargs)

  def parse_args(self, *args, **kwargs):

    args = super().parse_args(*args, **kwargs)
    return args

