import click
import os
import subprocess 
import ast


def cdToRoot( config ):

  subprocess.run( [ 'cd', config.root ] )


class Config:

  def __init__( self ):

    self.root = os.path.dirname( __file__ ) + '/../..'
    self.verbose = False

passConfig = click.make_pass_decorator( Config, ensure=True )



@click.group()
@passConfig
def cli( config ):
  """
  Welcome to the Personal Finance CLI
  """
  config.verbose = True


@cli.command() 
@click.option( '-gt', '--google-test', is_flag=True, default=False )
@click.option( '-h', '--help', is_flag=True, default=False )
@passConfig
def configure( config, google_test, help ): 
  """
  Configure this project's build
  """  
  lst = [ './tools/bash/configure.sh' ]

  #
  # Append configuration options
  #
  if google_test:
    lst.extend( [ '--google-test' ] )

  if help:
    lst.extend( [ '--help' ] )


  cdToRoot( config )
  subprocess.call( lst )



@cli.command()
@passConfig
def clean( config ):
  """
  Clean all generated files
  """
  cdToRoot( config )
  subprocess.call( [ './tools/bash/clean.sh' ] )


@cli.command()
@passConfig
def build( config ):
  """
  Build this project
  """
  cdToRoot( config )
  subprocess.call( [ './tools/bash/build.sh' ] )


@cli.command()
@passConfig
def install( config ):
  """
  Install this project
  """
  cdToRoot( config )
  subprocess.call( [ './tools/bash/install.sh' ] )


@cli.command()
@passConfig
def openDoxygen( config ):
  """
  Open HTML Doxygen-generated documentation for this project
  """

  cdToRoot( config )
  subprocess.run( [ 'open', 'docs/html/index.html' ] )









