open Data;

let getExn =
  fun
  | Field(x) => x
  | Missing => [%assert "getExn"];

let mapWithDefaultU = (opt, default, f) =>
  switch (opt) {
  | Field(x) => f(. x)
  | Missing => default
  };

let mapWithDefault = (opt, default, f) =>
  mapWithDefaultU(opt, default, (. x) => f(x));

let mapU = (opt, f) =>
  switch (opt) {
  | Field(x) => Field(f(. x))
  | Missing => Missing
  };

let map = (opt, f) => mapU(opt, (. x) => f(x));

let flatMapU = (opt, f) =>
  switch (opt) {
  | Field(x) => f(. x)
  | Missing => Missing
  };

let flatMap = (opt, f) => flatMapU(opt, (. x) => f(x));

let getWithDefault = (opt, default) =>
  switch (opt) {
  | Field(x) => x
  | Missing => default
  };

let isField =
  fun
  | Field(_) => true
  | Missing => false;

let isMissing = x => x == Missing;

let eqU = (a, b, f) =>
  switch (a) {
  | Field(a) =>
    switch (b) {
    | Missing => false
    | Field(b) => f(. a, b)
    }
  | Missing => b == Missing
  };

let eq = (a, b, f) => eqU(a, b, (. x, y) => f(x, y));

let cmpU = (a, b, f) =>
  switch (a, b) {
  | (Field(a), Field(b)) => f(. a, b)
  | (Missing, Field(_)) => (-1)
  | (Field(_), Missing) => 1
  | (Missing, Missing) => 0
  };

let cmp = (a, b, f) => cmpU(a, b, (. x, y) => f(x, y));