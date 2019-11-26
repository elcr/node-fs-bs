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


let fromUnknown = (unknown: Js.t('a)) => {
    let func: (Js.t('a), systemError('b) => t('b), otherError => t('b)) => t('b) =
        [%bs.raw {|
            function (unknown, makeSystemError, makeOtherError) {
                return unknown.syscall === undefined
                    ? makeOtherError(unknown)
                    : makeSystemError(unknown)
            }
        |}];
    func(
        unknown,
        unknown => SystemError(unknown),
        unknown => OtherError(unknown)
    )
};
