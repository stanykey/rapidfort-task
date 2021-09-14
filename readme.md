# My coding task for RapidFort

## Server
- start to listen given `port`
- create a session for each new connection
  - read request with the `count` of required `primes`
  - send required `count` of primes with some `delay`

## Client
- connect to the server via `IP` and `port`
- send request get `fixed` count of `primes numbers`
- receive numbers one-by-one
  - store them in `lexicographically` order
  - each time `top 5` changed print then to console
