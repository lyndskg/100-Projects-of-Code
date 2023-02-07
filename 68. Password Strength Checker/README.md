# 68. Password Strength Checker

<p align="center">
<img width="600" alt="HSIMP" src="https://techstacker.com/static/cd64a84f932dfc7a3f5e44fd02828ae3/12d0d/how-to-test-how-secure-your-password-is.jpg"> 
</p>

## Overview 

<ins>__Language__</ins>: JavaScript

<ins>__Completed on__</ins>: February 2nd, 2023

A JS plug-in used to check how strong a given password is. Built using the npm package ["hsimp-main"](https://www.npmjs.com/package/hsimp-main?activeTab=explore) for Node.js. Code is borrowed from the MIT-licensed "How Secure Is My Password?" (HSIMP) project &mdash; as deployed via the official Security.org toolkit [here](https://www.security.org/how-secure-is-my-password/), with source code available at [this Git repo](https://github.com/howsecureismypassword/hsimp).


## To Do

Almost fully implemented; needs to be tested and debugged.

## Usage

The `checker` function takes two arguments: a configuration object and an HTML `<input>` element

```javascript
checker({
    options: {
        calculationsPerSecond: 1e10, // 10 billion,
        good: 31557600e3, // 1,000 years
        ok: 31557600 // 1 year
    },
    outputTime: function (time, input) {
        console.log(time, input);
    },
    outputChecks: function (checks, input) {
        console.log(checks, input);
    }
}, document.getElementById("password"));
```

## Configuration

The configuration object supports three properties:

- `options`: an object of options that affect calculations
- `outputTime`: a function that is passed the length of time it would take to crack the given password
- `outputChecks`: a function that is passed a list of results from various checks

### `options`

Currently there are three supported options:

- `calculationsPerSecond`: the assumed number of calculations per second a cracker could make (default: 10e9 - 10 billion)
- `good`: the minimum time (in seconds) that a "good" (green) password would take to crack (default: 31557600e6 - 1 million years)
- `ok`: the minimum time (in seconds) that an "ok" (orange) password would take to crack (default: 31557600 - 1 year)

### `outputTime`

The `outputTime` function is passed two variables: the time it would take to crack the password (as a human-readable string) and (optionally) the input which it refers to.

```javascript
var renderTime = function (time, input) {
    document.getElementById("password-strength").innerHTML = time;
}

checker({ outputTime: renderTime }, document.getElementById("password"));
```

### `outputChecks`

The `outputChecks` function is passed two variables: an array of check results and (optionally) the input which it refers to.

Each check result is an object with three properties:

- `name`: the check name/title
- `message`: some explanatory text
- `level`: the severity level (insecure, warning, notice, achievement)

```javascript
{
    name: "Length: Very Short",
    message: "Your password is very short. The longer a password is the more secure it will be.",
    level: "warning"
}
```


## Currying

The `checker` function supports currying. This means you can set the options once and then use the returned function to setup more than one input:

```javascript
var attachHSIMP = checker({
    // shared options here
});

attachHSIMP(document.getElementById("input-1"));
attachHSIMP(document.getElementById("input-2"));
```