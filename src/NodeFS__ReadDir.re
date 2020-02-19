open Relude.Globals;

module Error = NodeFS__Error;


module DirectoryEntry = {
    type t = {
        name: string
    };

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
};


type _readDirOptions = {
    withFileTypes: bool,
    encoding: string
};


[@bs.module "fs"]
external _readDir : (
    string,
    _readDirOptions,
    (Js.Null.t(Js.Exn.t), array(DirectoryEntry.t)) => unit
) => unit = "readdir";


let readDir = (~encoding="utf-8", path) =>
    IO.async(resolve =>
        _readDir(path, { withFileTypes: true, encoding }, (error, files) =>
            Js.Null.toOption(error)
                |> Result.fromOption(files)
                |> Result.flip
                |> Result.mapError(Error.fromException)
                |> resolve
        )
    );
