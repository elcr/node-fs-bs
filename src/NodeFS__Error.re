module SystemError = {
    type t('a) = {
        address: Js.Nullable.t(string),
        code: string,
        dest: Js.Nullable.t(string),
        errno: float,
        info: Js.Nullable.t('a),
        message: string,
        path: Js.Nullable.t(string),
        port: Js.Nullable.t(int),
        syscall: string
    };
};


module UnknownError = {
    type t = {
        code: string,
        message: string
    };
};


type t =
    | AccessDenied(SystemError.t('a)) : t
    | AddressInUse(SystemError.t('a)) : t
    | ConnectionRefused(SystemError.t('a)) : t
    | ConnectionReset(SystemError.t('a)) : t
    | FileExists(SystemError.t('a)) : t
    | IsADirectory(SystemError.t('a)) : t
    | TooManyOpenFiles(SystemError.t('a)) : t
    | NoSuchFileOrDirectory(SystemError.t('a)) : t
    | NotADirectory(SystemError.t('a)) : t
    | DirectoryNotEmpty(SystemError.t('a)) : t
    | DNSLookupFailed(SystemError.t('a)) : t
    | NotPermitted(SystemError.t('a)) : t
    | BrokenPipe(SystemError.t('a)) : t
    | TimedOut(SystemError.t('a)) : t
    | UnknownSystemError(SystemError.t('a)) : t
    | OtherUnknownError(UnknownError.t) : t;


let _makeSystemError = (exc: SystemError.t('a)) => {
    switch (exc.code) {
        | "EACCES" => AccessDenied(exc)
        | "EADDRINUSE" => AddressInUse(exc)
        | "ECONNREFUSED" => ConnectionRefused(exc)
        | "ECONNRESET" => ConnectionReset(exc)
        | "EEXIST" => FileExists(exc)
        | "EISDIR" => IsADirectory(exc)
        | "EMFILE" => TooManyOpenFiles(exc)
        | "ENOENT" => NoSuchFileOrDirectory(exc)
        | "ENOTDIR" => NotADirectory(exc)
        | "ENOTEMPTY" => DirectoryNotEmpty(exc)
        | "ENOTFOUND" => DNSLookupFailed(exc)
        | "EPERM" => NotPermitted(exc)
        | "EPIPE" => BrokenPipe(exc)
        | "ETIMEDOUT" => TimedOut(exc)
        | _ => UnknownSystemError(exc)
    }
};


let _makeUnknownError = exc => OtherUnknownError(exc);


let fromException = exc => {
    let _makeError: (
        SystemError.t('a) => t,
        UnknownError.t => t,
        Js.Exn.t
    ) => t = [%bs.raw {|
        function (makeSystemError, makeUnknownError, exc) {
            return exc.syscall === undefined
                ? makeUnknownError(exc)
                : makeSystemError(exc)
        }
    |}];

    _makeError(_makeSystemError, _makeUnknownError, exc)
};
