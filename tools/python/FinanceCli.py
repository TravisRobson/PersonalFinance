#!/usr/bin/env python3

import click
import os
import subprocess 
import ast


class AliasedGroup( click.Group ):
  """
  This function was taken from Click themselves
  http://click.palletsprojects.com/en/5.x/advanced/
  """
  def get_command( self, ctx, cmd_name ):

    rv = click.Group.get_command(self, ctx, cmd_name)
    
    if rv is not None:
      return rv

    matches = [x for x in self.list_commands(ctx)
               if x.startswith(cmd_name)]
    if not matches:
      return None

    elif len(matches) == 1:
      return click.Group.get_command( self, ctx, matches[0] )

    ctx.fail('Too many matches: %s' % ', '.join(sorted(matches)))


def cdToRoot( config ):

  subprocess.call( [ 'cd', config.root ] )


class Config:

  def __init__( self ):

    self.root = os.path.dirname( __file__ ) + '/../..'
    self.verbose = False

passConfig = click.make_pass_decorator( Config, ensure=True )



@click.group( cls=AliasedGroup )
@passConfig
def cli( config ):
  """
  Welcome to the Personal Finance CLI
  """
  config.verbose = True




@cli.command() 
@click.option( '-gt', '--google-test', is_flag=True, default=False )
@click.option( '-h', '--help', is_flag=True, default=False )
@click.option( '-i', '--install-prefix' )
@click.option( '-nw', '--no-warnings', is_flag=True, default=False )
@click.option( '-vb', '--verbose-build', is_flag=True, default=False )
@passConfig
def configure( config, google_test, help, install_prefix, no_warnings, verbose_build ): 
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

  if no_warnings:
    lst.extend( [ '--no-warnings' ] )

  if verbose_build:
    lst.extend( [ '--verbose-build' ] )

  if install_prefix is not None:
    lst.extend( [ '--install-prefix', '{}'.format( install_prefix ) ] )

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
@click.pass_context
def bi( context, config ):
  """
  Build and install
  """
  context.invoke( build   )
  context.invoke( install )



@cli.command( cls=AliasedGroup )
@passConfig
def openDoxygen( config ):
  """
  Open HTML Doxygen-generated documentation for this project
  """
  cdToRoot( config )
  subprocess.call( [ 'open', 'docs/html/index.html' ] )









