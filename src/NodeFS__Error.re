module JsError = NodeFS__JsError;


module SystemError = {
    type t('a) = {
        address: option(string),
        code: string,
        dest: option(string),
        errno: float,
        info: option(Js.t('a)),
        message: string,
        path: option(string),
        port: option(int),
        syscall: string
    };

    let fromJsError = (error: JsError.systemError('a)) => {
        address: Js.Nullable.toOption(error##address),
        code: error##code,
        dest: Js.Nullable.toOption(error##dest),
        errno: error##errno,
        info: Js.Nullable.toOption(error##info),
        message: error##message,
        path: Js.Nullable.toOption(error##path),
        port: Js.Nullable.toOption(error##port),
        syscall: error##syscall
    };
};


module OtherError = {
    type t = {
        code: string,
        message: string
    };

    let fromJsError = (error: JsError.otherError) => {
        code: error##code,
        message: error##message
    };
};


type t('a) =
    | AccessDenied(SystemError.t('a))
    | AddressInUse(SystemError.t('a))
    | ConnectionRefused(SystemError.t('a))
    | ConnectionReset(SystemError.t('a))
    | FileExists(SystemError.t('a))
    | IsADirectory(SystemError.t('a))
    | TooManyOpenFiles(SystemError.t('a))
    | NoSuchFileOrDirectory(SystemError.t('a))
    | NotADirectory(SystemError.t('a))
    | DirectoryNotEmpty(SystemError.t('a))
    | DNSLookupFailed(SystemError.t('a))
    | NotPermitted(SystemError.t('a))
    | BrokenPipe(SystemError.t('a))
    | TimedOut(SystemError.t('a))
    | UnknownSystemError(SystemError.t('a))
    | UnknownOtherError(OtherError.t);


let fromJsError = error => {
    switch (error) {
        | JsError.OtherError(error) => {
            OtherError.fromJsError(error)
                |. UnknownOtherError
        }
        | SystemError(error) => {
            let errorRecord = SystemError.fromJsError(error);
            switch (errorRecord.code) {
                | "EACCES" => AccessDenied(errorRecord)
                | "EADDRINUSE" => AddressInUse(errorRecord)
                | "ECONNREFUSED" => ConnectionRefused(errorRecord)
                | "ECONNRESET" => ConnectionReset(errorRecord)
                | "EEXIST" => FileExists(errorRecord)
                | "EISDIR" => IsADirectory(errorRecord)
                | "EMFILE" => TooManyOpenFiles(errorRecord)
                | "ENOENT" => NoSuchFileOrDirectory(errorRecord)
                | "ENOTDIR" => NotADirectory(errorRecord)
                | "ENOTEMPTY" => DirectoryNotEmpty(errorRecord)
                | "ENOTFOUND" => DNSLookupFailed(errorRecord)
                | "EPERM" => NotPermitted(errorRecord)
                | "EPIPE" => BrokenPipe(errorRecord)
                | "ETIMEDOUT" => TimedOut(errorRecord)
                | _ => UnknownSystemError(errorRecord)
            }
        }
    }
}
