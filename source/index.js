import emscriptenTest from '../dist/emscripten-test.js';

class EmscriptenTest {
    constructor (Module) {
        this._Module = Module;
    }

    fancyAlgorithm () {
        const result = this._Module._fancyAlgorithm();
        this._Module.emscriptenTestFlush();
        return result;
    }
}

const createEmscriptenTest = async function () {
    const ModuleIn = {
        arguments: ['--exit']
    };
    const ENVIRONMENT_IS_NODE = typeof process === "object" && typeof process.versions === "object" && typeof process.versions.node === "string";
    if (ENVIRONMENT_IS_NODE) {
        ModuleIn.locateFile = function (path, prefix) {
            if (path.endsWith('.wasm')) {
                return __dirname + '/emscriptenTest.wasm';
            }
            return prefix + path;
        };
        ModuleIn.quit = function (status, toThrow) {
            throw toThrow;
        };
    }
    const Module = await emscriptenTest(ModuleIn);
    return new EmscriptenTest(Module);
};

export {createEmscriptenTest};
