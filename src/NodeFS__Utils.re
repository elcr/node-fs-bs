[@bs.new]
external makePromise : (
    ('a => unit, Js.Exn.t => unit) => unit
) => Js.Promise.t('a) = "Promise";


external promiseErrorToException : Js.Promise.error => Js.Exn.t = "%identity";
