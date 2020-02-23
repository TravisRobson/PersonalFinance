

from setuptools import setup


setup(
  name = 'Finance',
  version = 0.1, 
  py_modules = [ 'FinanceCli' ],
  install_requires = [
    'Click'
  ],
  entry_points = '''
    [console_scripts]
    Finance=FinanceCli:cli
  '''
)