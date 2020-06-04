open Relude.Globals;


type t = {
    dev: int,
    ino: int,
    mode: int,
    nlink: int,
    uid: int,
    gid: int,
    rdev: int,
    size: int,
    blksize: int,
    blocks: int,
    atimeMs: float,
    mtimeMs: float,
    ctimeMs: float,
    birthtimeMs: float,
    atime: Js.Date.t,
    mtime: Js.Date.t,
    ctime: Js.Date.t,
    birthtime: Js.Date.t
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


[@bs.module "fs"]
external _stat : (
    string,
    (Js.Null.t(Js.Exn.t), t) => unit
) => unit = "stat";


let stat = path =>
    IO.async(resolve =>
        _stat(path, (error, data) =>
            Js.Null.toOption(error)
                |> Result.fromOption(data)
                |> Result.flip
                |> Result.mapError(NodeFS__Error.fromException)
                |> resolve
        )
    );
