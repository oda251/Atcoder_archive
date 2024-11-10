#!/usr/local/bin/node
// please change the path to your node path

import { fileURLToPath } from 'url';
import { exec } from 'child_process';

// 現在のファイルのURLを取得
const file_path = fileURLToPath(import.meta.url);
console.error(`file_path: ${file_path}`);

const CXX = 'g++';
const CXXFLAGS = '-std=c++17 -Wall -Wextra -O2 -DONLINE_JUDGE';
const INCLUDE = '-I~/.ac-library';
const NAME = 'out';
exec(`${CXX} ${CXXFLAGS} ${INCLUDE} ${file_path} -o ${NAME}`, (err, stdout, stderr) => {
  if (err) {
    console.error(err);
    return;
  }
  console.log('Compiled successfully');
});