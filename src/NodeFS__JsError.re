type systemError('a) = {
    .
    "address": Js.Nullable.t(string),
    "code": string,
    "dest": Js.Nullable.t(string),
    "errno": float,
    "info": Js.Nullable.t('a),
    "message": string,
    "path": Js.Nullable.t(string),
    "port": Js.Nullable.t(int),
    "syscall": string
};


type otherError = {
    .
    "code": string,
    "message": string
};


type t('a) =
    | SystemError(systemError('a))
    | OtherError(otherError);


let fromException = exc => {
    let func: (
        systemError('a) => t('a),
        otherError => t('a),
        Js.Exn.t
    ) => t('a) =
        [%bs.raw {|
            function (makeSystemError, makeOtherError, exc) {
                return exc.syscall === undefined
                    ? makeOtherError(exc)
                    : makeSystemError(exc)
            }
        |}];
    func(exc => SystemError(exc), exc => OtherError(exc), exc)
};
