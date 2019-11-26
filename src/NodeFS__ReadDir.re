open Rebase;

module Error = NodeFS__Error;
module JsError = NodeFS__JsError;


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


[@bs.module "fs"]
external _readDir : (
    string,
    {
        .
        "withFileTypes": bool,
        "encoding": Js.Nullable.t(string)
    },
    (Js.Nullable.t(Js.Exn.t), array(DirectoryEntry.t)) => unit
) => unit = "readdir";


let readDir = (~encoding=?, path) => {
    FutureBS.make(resolve => {
        let options = {
            "withFileTypes": true,
            "encoding": Js.Nullable.fromOption(encoding)
        };
        _readDir(path, options, (error, files) => {
            Js.Nullable.toOption(error)
                |> Option.map(error => {
                    JsError.fromException(error)
                        |> Error.fromJsError
                        |. Error
                })
                |> Option.getOr(Ok(files))
                |> resolve
        })
    })
};
