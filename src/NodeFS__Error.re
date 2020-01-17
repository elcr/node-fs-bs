module SystemError = {
    type t('a) = {
        address: option(string),
        code: string,
        dest: option(string),
        errno: float,
        info: option('a),
        message: string,
        path: option(string),
        port: option(int),
        syscall: string
    };

    type js('a) = {
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

    let fromJs = ({ address, code, dest, errno, info, message, path, port, syscall }: js('a)): t('a) => {
        address: Js.Nullable.toOption(address),
        code,
        dest: Js.Nullable.toOption(dest),
        errno,
        info: Js.Nullable.toOption(info),
        message,
        path: Js.Nullable.toOption(path),
        port: Js.Nullable.toOption(port),
        syscall
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


let _makeSystemError = exc => {
    let error = SystemError.fromJs(exc);
    switch (error.code) {
        | "EACCES" => AccessDenied(error)
        | "EADDRINUSE" => AddressInUse(error)
        | "ECONNREFUSED" => ConnectionRefused(error)
        | "ECONNRESET" => ConnectionReset(error)
        | "EEXIST" => FileExists(error)
        | "EISDIR" => IsADirectory(error)
        | "EMFILE" => TooManyOpenFiles(error)
        | "ENOENT" => NoSuchFileOrDirectory(error)
        | "ENOTDIR" => NotADirectory(error)
        | "ENOTEMPTY" => DirectoryNotEmpty(error)
        | "ENOTFOUND" => DNSLookupFailed(error)
        | "EPERM" => NotPermitted(error)
        | "EPIPE" => BrokenPipe(error)
        | "ETIMEDOUT" => TimedOut(error)
        | _ => UnknownSystemError(error)
    }
};


let _makeUnknownError = exc => OtherUnknownError(exc);


let fromException = exc => {
    let _makeError: (
        SystemError.js('a) => t,
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
