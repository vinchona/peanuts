#!/bin/bash

function check_existence_of()
{
  local readonly program="$1"
  if [ -z $(command -v "$program") ]; then
    echo "Reformating requires '"$program"'" 1>&2
    echo "Please install it" 1>&2
    exit 1
  fi
}

function check_version_of()
{
  local readonly required_program="$1"
  check_existence_of "$required_program"
  local readonly required_version="$2"
  local readonly current_version=$($required_program --version)
  echo $current_version | grep -q $required_version
  local readonly version_exist="$?"
  if [ "$version_exist" -ne 0 ]; then
    echo "Bad version of $required_program, skipping formatting" 1>&2
    echo "Required: $required_version" 1>&2
    echo "Current: $current_version" 1>&2
    exit 1
  fi
}

function files()
{
  find . -name "*.hpp" -or -name "*.cpp" -or -name "*.h" -or -name "*.c" -or -name "cxx"
}

function replace_if_diff()
{
  local readonly original_file="$1"
  local readonly formated_file="$2"
  if ! diff -Naur "$original_file" "$formated_file" ; then
    echo "Format $original_file"
    mv "$formated_file" "$original_file"
  else
    rm "$formated_file"
  fi
}

function reformat_file()
{
  local readonly original_file="$1"
  local readonly formated_file="$original_file.formated"
  clang-format -style=file "$original_file" 1> "$formated_file"
  replace_if_diff "$original_file" "$formated_file"
}

function reformat_all_files()
{
  echo "Reformatting.."
  files | while read file; do
    reformat_file "$file"
  done
}

check_version_of 'clang-format' '8.0'
reformat_all_files
