#!/bin/bash

cd afs_util
mkdir output
cargo run --release -- -e ../Z_DATA.BIN output
