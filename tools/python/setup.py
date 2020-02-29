

from setuptools import setup


setup(
  name = 'PersonalFinance',
  version = 0.1, 
  py_modules = [ 'FinanceCli' ],
  install_requires = [
    'Click'
  ],
  entry_points = '''
    [console_scripts]
    pf=FinanceCli:cli
  '''
)