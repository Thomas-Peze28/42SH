#!/bin/bash
cp -r /src/* /doit
cd /doit
/bin/epitfl
cp -r output_final /src/epitfl_output
rm -rf /doit