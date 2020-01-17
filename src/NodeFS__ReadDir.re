open Relude.Globals;

module Error = NodeFS__Error;
module Utils = NodeFS__Utils;


module DirectoryEntry = {
    type t;

    [@bs.send]
    external isBlockDevice : t => bool = "isBlockDevice";

    [@bs.send]
    external isCharacterDevice : t => bool = "isCharacterDevice";

    [@bs.send]
    external isDirectory : t => bool = "isDirectory";

    [@bs.send]
    external isFIFO : t => bool = "isFIFO";

    [@bs.send]
    external isFile : t => bool = "isFile";

    [@bs.send]
    external isSocket : t => bool = "isSocket";

    [@bs.send]
    external isSymbolicLink : t => bool = "isSymbolicLink";

    [@bs.get]
    external getName : t => string = "name";
};


type _readDirOptions = {
    withFileTypes: bool,
    encoding: string
};


[@bs.module "fs"]
external _readDir : (
    string,
    _readDirOptions,
    (Js.Nullable.t(Js.Exn.t), array(DirectoryEntry.t)) => unit
) => unit = "readdir";


let readDir = (~encoding="utf-8", path) => {
    let io = Relude.Js.Promise.toIOLazy(() => {
        Utils.makePromise((resolve, reject) => {
            _readDir(path, { withFileTypes: true, encoding }, (error, files) => {
                let result = Js.Nullable.toOption(error)
                    |> Result.fromOption(files)
                    |> Result.flip;
                switch (result) {
                    | Ok(files) => resolve(files)
                    | Error(error) => reject(error)
                }
            })
        })
    });
    IO.mapError(promiseError => {
        Utils.promiseErrorToException(promiseError)
            |> Error.fromException
    }, io)
};
