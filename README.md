# emscripten-test
 
Steps to use on code spaces:

1. Create the codespace from master
2. Run the following commands for first time setup: `npm install`, `npm run checkout:submodule`, `npm run install:emsdk:nix`
3. Run the following command to build: `npm run build:win`
4. For manual tests run: `npm run test:browser-module` and / or `npm run test:wasmer`
