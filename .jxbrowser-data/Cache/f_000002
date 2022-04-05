(function(){/*

 Copyright The Closure Library Authors.
 SPDX-License-Identifier: Apache-2.0
*/
'use strict';var l;function aa(a){var b=0;return function(){return b<a.length?{done:!1,value:a[b++]}:{done:!0}}}
var ba="function"==typeof Object.defineProperties?Object.defineProperty:function(a,b,c){if(a==Array.prototype||a==Object.prototype)return a;a[b]=c.value;return a};
function ca(a){a=["object"==typeof globalThis&&globalThis,a,"object"==typeof window&&window,"object"==typeof self&&self,"object"==typeof global&&global];for(var b=0;b<a.length;++b){var c=a[b];if(c&&c.Math==Math)return c}throw Error("Cannot find global object");}
var da=ca(this);function n(a,b){if(b)a:{var c=da;a=a.split(".");for(var d=0;d<a.length-1;d++){var e=a[d];if(!(e in c))break a;c=c[e]}a=a[a.length-1];d=c[a];b=b(d);b!=d&&null!=b&&ba(c,a,{configurable:!0,writable:!0,value:b})}}
n("Symbol",function(a){function b(f){if(this instanceof b)throw new TypeError("Symbol is not a constructor");return new c(d+(f||"")+"_"+e++,f)}
function c(f,g){this.h=f;ba(this,"description",{configurable:!0,writable:!0,value:g})}
if(a)return a;c.prototype.toString=function(){return this.h};
var d="jscomp_symbol_"+(1E9*Math.random()>>>0)+"_",e=0;return b});
n("Symbol.iterator",function(a){if(a)return a;a=Symbol("Symbol.iterator");for(var b="Array Int8Array Uint8Array Uint8ClampedArray Int16Array Uint16Array Int32Array Uint32Array Float32Array Float64Array".split(" "),c=0;c<b.length;c++){var d=da[b[c]];"function"===typeof d&&"function"!=typeof d.prototype[a]&&ba(d.prototype,a,{configurable:!0,writable:!0,value:function(){return ea(aa(this))}})}return a});
function ea(a){a={next:a};a[Symbol.iterator]=function(){return this};
return a}
function p(a){var b="undefined"!=typeof Symbol&&Symbol.iterator&&a[Symbol.iterator];return b?b.call(a):{next:aa(a)}}
function fa(a){if(!(a instanceof Array)){a=p(a);for(var b,c=[];!(b=a.next()).done;)c.push(b.value);a=c}return a}
function ha(a,b){return Object.prototype.hasOwnProperty.call(a,b)}
var ia="function"==typeof Object.assign?Object.assign:function(a,b){for(var c=1;c<arguments.length;c++){var d=arguments[c];if(d)for(var e in d)ha(d,e)&&(a[e]=d[e])}return a};
n("Object.assign",function(a){return a||ia});
var ja="function"==typeof Object.create?Object.create:function(a){function b(){}
b.prototype=a;return new b},la=function(){function a(){function c(){}
new c;Reflect.construct(c,[],function(){});
return new c instanceof c}
if("undefined"!=typeof Reflect&&Reflect.construct){if(a())return Reflect.construct;var b=Reflect.construct;return function(c,d,e){c=b(c,d);e&&Reflect.setPrototypeOf(c,e.prototype);return c}}return function(c,d,e){void 0===e&&(e=c);
e=ja(e.prototype||Object.prototype);return Function.prototype.apply.call(c,e,d)||e}}(),ma;
if("function"==typeof Object.setPrototypeOf)ma=Object.setPrototypeOf;else{var na;a:{var oa={a:!0},pa={};try{pa.__proto__=oa;na=pa.a;break a}catch(a){}na=!1}ma=na?function(a,b){a.__proto__=b;if(a.__proto__!==b)throw new TypeError(a+" is not extensible");return a}:null}var qa=ma;
function r(a,b){a.prototype=ja(b.prototype);a.prototype.constructor=a;if(qa)qa(a,b);else for(var c in b)if("prototype"!=c)if(Object.defineProperties){var d=Object.getOwnPropertyDescriptor(b,c);d&&Object.defineProperty(a,c,d)}else a[c]=b[c];a.aa=b.prototype}
function ra(){this.C=!1;this.l=null;this.i=void 0;this.h=1;this.o=this.m=0;this.A=this.j=null}
function sa(a){if(a.C)throw new TypeError("Generator is already running");a.C=!0}
ra.prototype.u=function(a){this.i=a};
function va(a,b){a.j={ub:b,yb:!0};a.h=a.m||a.o}
ra.prototype.return=function(a){this.j={return:a};this.h=this.o};
function t(a,b,c){a.h=c;return{value:b}}
ra.prototype.s=function(a){this.h=a};
function wa(a,b,c){a.m=b;void 0!=c&&(a.o=c)}
function xa(a,b){a.h=b;a.m=0}
function ya(a){a.m=0;var b=a.j.ub;a.j=null;return b}
function za(a){a.A=[a.j];a.m=0;a.o=0}
function Aa(a){var b=a.A.splice(0)[0];(b=a.j=a.j||b)?b.yb?a.h=a.m||a.o:void 0!=b.s&&a.o<b.s?(a.h=b.s,a.j=null):a.h=a.o:a.h=0}
function Da(a){this.h=new ra;this.i=a}
function Ea(a,b){sa(a.h);var c=a.h.l;if(c)return Fa(a,"return"in c?c["return"]:function(d){return{value:d,done:!0}},b,a.h.return);
a.h.return(b);return Ga(a)}
function Fa(a,b,c,d){try{var e=b.call(a.h.l,c);if(!(e instanceof Object))throw new TypeError("Iterator result "+e+" is not an object");if(!e.done)return a.h.C=!1,e;var f=e.value}catch(g){return a.h.l=null,va(a.h,g),Ga(a)}a.h.l=null;d.call(a.h,f);return Ga(a)}
function Ga(a){for(;a.h.h;)try{var b=a.i(a.h);if(b)return a.h.C=!1,{value:b.value,done:!1}}catch(c){a.h.i=void 0,va(a.h,c)}a.h.C=!1;if(a.h.j){b=a.h.j;a.h.j=null;if(b.yb)throw b.ub;return{value:b.return,done:!0}}return{value:void 0,done:!0}}
function Ha(a){this.next=function(b){sa(a.h);a.h.l?b=Fa(a,a.h.l.next,b,a.h.u):(a.h.u(b),b=Ga(a));return b};
this.throw=function(b){sa(a.h);a.h.l?b=Fa(a,a.h.l["throw"],b,a.h.u):(va(a.h,b),b=Ga(a));return b};
this.return=function(b){return Ea(a,b)};
this[Symbol.iterator]=function(){return this}}
function Ia(a){function b(d){return a.next(d)}
function c(d){return a.throw(d)}
return new Promise(function(d,e){function f(g){g.done?d(g.value):Promise.resolve(g.value).then(b,c).then(f,e)}
f(a.next())})}
function w(a){return Ia(new Ha(new Da(a)))}
function Ja(){for(var a=Number(this),b=[],c=a;c<arguments.length;c++)b[c-a]=arguments[c];return b}
n("Reflect",function(a){return a?a:{}});
n("Reflect.construct",function(){return la});
n("Reflect.setPrototypeOf",function(a){return a?a:qa?function(b,c){try{return qa(b,c),!0}catch(d){return!1}}:null});
n("Promise",function(a){function b(g){this.h=0;this.j=void 0;this.i=[];this.C=!1;var h=this.l();try{g(h.resolve,h.reject)}catch(k){h.reject(k)}}
function c(){this.h=null}
function d(g){return g instanceof b?g:new b(function(h){h(g)})}
if(a)return a;c.prototype.i=function(g){if(null==this.h){this.h=[];var h=this;this.j(function(){h.o()})}this.h.push(g)};
var e=da.setTimeout;c.prototype.j=function(g){e(g,0)};
c.prototype.o=function(){for(;this.h&&this.h.length;){var g=this.h;this.h=[];for(var h=0;h<g.length;++h){var k=g[h];g[h]=null;try{k()}catch(m){this.l(m)}}}this.h=null};
c.prototype.l=function(g){this.j(function(){throw g;})};
b.prototype.l=function(){function g(m){return function(q){k||(k=!0,m.call(h,q))}}
var h=this,k=!1;return{resolve:g(this.T),reject:g(this.o)}};
b.prototype.T=function(g){if(g===this)this.o(new TypeError("A Promise cannot resolve to itself"));else if(g instanceof b)this.fa(g);else{a:switch(typeof g){case "object":var h=null!=g;break a;case "function":h=!0;break a;default:h=!1}h?this.M(g):this.m(g)}};
b.prototype.M=function(g){var h=void 0;try{h=g.then}catch(k){this.o(k);return}"function"==typeof h?this.na(h,g):this.m(g)};
b.prototype.o=function(g){this.u(2,g)};
b.prototype.m=function(g){this.u(1,g)};
b.prototype.u=function(g,h){if(0!=this.h)throw Error("Cannot settle("+g+", "+h+"): Promise already settled in state"+this.h);this.h=g;this.j=h;2===this.h&&this.Y();this.A()};
b.prototype.Y=function(){var g=this;e(function(){if(g.L()){var h=da.console;"undefined"!==typeof h&&h.error(g.j)}},1)};
b.prototype.L=function(){if(this.C)return!1;var g=da.CustomEvent,h=da.Event,k=da.dispatchEvent;if("undefined"===typeof k)return!0;"function"===typeof g?g=new g("unhandledrejection",{cancelable:!0}):"function"===typeof h?g=new h("unhandledrejection",{cancelable:!0}):(g=da.document.createEvent("CustomEvent"),g.initCustomEvent("unhandledrejection",!1,!0,g));g.promise=this;g.reason=this.j;return k(g)};
b.prototype.A=function(){if(null!=this.i){for(var g=0;g<this.i.length;++g)f.i(this.i[g]);this.i=null}};
var f=new c;b.prototype.fa=function(g){var h=this.l();g.Ia(h.resolve,h.reject)};
b.prototype.na=function(g,h){var k=this.l();try{g.call(h,k.resolve,k.reject)}catch(m){k.reject(m)}};
b.prototype.then=function(g,h){function k(C,v){return"function"==typeof C?function(E){try{m(C(E))}catch(F){q(F)}}:v}
var m,q,u=new b(function(C,v){m=C;q=v});
this.Ia(k(g,m),k(h,q));return u};
b.prototype.catch=function(g){return this.then(void 0,g)};
b.prototype.Ia=function(g,h){function k(){switch(m.h){case 1:g(m.j);break;case 2:h(m.j);break;default:throw Error("Unexpected state: "+m.h);}}
var m=this;null==this.i?f.i(k):this.i.push(k);this.C=!0};
b.resolve=d;b.reject=function(g){return new b(function(h,k){k(g)})};
b.race=function(g){return new b(function(h,k){for(var m=p(g),q=m.next();!q.done;q=m.next())d(q.value).Ia(h,k)})};
b.all=function(g){var h=p(g),k=h.next();return k.done?d([]):new b(function(m,q){function u(E){return function(F){C[E]=F;v--;0==v&&m(C)}}
var C=[],v=0;do C.push(void 0),v++,d(k.value).Ia(u(C.length-1),q),k=h.next();while(!k.done)})};
return b});
n("WeakMap",function(a){function b(k){this.h=(h+=Math.random()+1).toString();if(k){k=p(k);for(var m;!(m=k.next()).done;)m=m.value,this.set(m[0],m[1])}}
function c(){}
function d(k){var m=typeof k;return"object"===m&&null!==k||"function"===m}
function e(k){if(!ha(k,g)){var m=new c;ba(k,g,{value:m})}}
function f(k){var m=Object[k];m&&(Object[k]=function(q){if(q instanceof c)return q;Object.isExtensible(q)&&e(q);return m(q)})}
if(function(){if(!a||!Object.seal)return!1;try{var k=Object.seal({}),m=Object.seal({}),q=new a([[k,2],[m,3]]);if(2!=q.get(k)||3!=q.get(m))return!1;q.delete(k);q.set(m,4);return!q.has(k)&&4==q.get(m)}catch(u){return!1}}())return a;
var g="$jscomp_hidden_"+Math.random();f("freeze");f("preventExtensions");f("seal");var h=0;b.prototype.set=function(k,m){if(!d(k))throw Error("Invalid WeakMap key");e(k);if(!ha(k,g))throw Error("WeakMap key fail: "+k);k[g][this.h]=m;return this};
b.prototype.get=function(k){return d(k)&&ha(k,g)?k[g][this.h]:void 0};
b.prototype.has=function(k){return d(k)&&ha(k,g)&&ha(k[g],this.h)};
b.prototype.delete=function(k){return d(k)&&ha(k,g)&&ha(k[g],this.h)?delete k[g][this.h]:!1};
return b});
n("Map",function(a){function b(){var h={};return h.previous=h.next=h.head=h}
function c(h,k){var m=h.h;return ea(function(){if(m){for(;m.head!=h.h;)m=m.previous;for(;m.next!=m.head;)return m=m.next,{done:!1,value:k(m)};m=null}return{done:!0,value:void 0}})}
function d(h,k){var m=k&&typeof k;"object"==m||"function"==m?f.has(k)?m=f.get(k):(m=""+ ++g,f.set(k,m)):m="p_"+k;var q=h.data_[m];if(q&&ha(h.data_,m))for(h=0;h<q.length;h++){var u=q[h];if(k!==k&&u.key!==u.key||k===u.key)return{id:m,list:q,index:h,entry:u}}return{id:m,list:q,index:-1,entry:void 0}}
function e(h){this.data_={};this.h=b();this.size=0;if(h){h=p(h);for(var k;!(k=h.next()).done;)k=k.value,this.set(k[0],k[1])}}
if(function(){if(!a||"function"!=typeof a||!a.prototype.entries||"function"!=typeof Object.seal)return!1;try{var h=Object.seal({x:4}),k=new a(p([[h,"s"]]));if("s"!=k.get(h)||1!=k.size||k.get({x:4})||k.set({x:4},"t")!=k||2!=k.size)return!1;var m=k.entries(),q=m.next();if(q.done||q.value[0]!=h||"s"!=q.value[1])return!1;q=m.next();return q.done||4!=q.value[0].x||"t"!=q.value[1]||!m.next().done?!1:!0}catch(u){return!1}}())return a;
var f=new WeakMap;e.prototype.set=function(h,k){h=0===h?0:h;var m=d(this,h);m.list||(m.list=this.data_[m.id]=[]);m.entry?m.entry.value=k:(m.entry={next:this.h,previous:this.h.previous,head:this.h,key:h,value:k},m.list.push(m.entry),this.h.previous.next=m.entry,this.h.previous=m.entry,this.size++);return this};
e.prototype.delete=function(h){h=d(this,h);return h.entry&&h.list?(h.list.splice(h.index,1),h.list.length||delete this.data_[h.id],h.entry.previous.next=h.entry.next,h.entry.next.previous=h.entry.previous,h.entry.head=null,this.size--,!0):!1};
e.prototype.clear=function(){this.data_={};this.h=this.h.previous=b();this.size=0};
e.prototype.has=function(h){return!!d(this,h).entry};
e.prototype.get=function(h){return(h=d(this,h).entry)&&h.value};
e.prototype.entries=function(){return c(this,function(h){return[h.key,h.value]})};
e.prototype.keys=function(){return c(this,function(h){return h.key})};
e.prototype.values=function(){return c(this,function(h){return h.value})};
e.prototype.forEach=function(h,k){for(var m=this.entries(),q;!(q=m.next()).done;)q=q.value,h.call(k,q[1],q[0],this)};
e.prototype[Symbol.iterator]=e.prototype.entries;var g=0;return e});
function Ka(a,b,c){if(null==a)throw new TypeError("The 'this' value for String.prototype."+c+" must not be null or undefined");if(b instanceof RegExp)throw new TypeError("First argument to String.prototype."+c+" must not be a regular expression");return a+""}
n("String.prototype.endsWith",function(a){return a?a:function(b,c){var d=Ka(this,b,"endsWith");b+="";void 0===c&&(c=d.length);c=Math.max(0,Math.min(c|0,d.length));for(var e=b.length;0<e&&0<c;)if(d[--c]!=b[--e])return!1;return 0>=e}});
n("Array.prototype.find",function(a){return a?a:function(b,c){a:{var d=this;d instanceof String&&(d=String(d));for(var e=d.length,f=0;f<e;f++){var g=d[f];if(b.call(c,g,f,d)){b=g;break a}}b=void 0}return b}});
n("String.prototype.startsWith",function(a){return a?a:function(b,c){var d=Ka(this,b,"startsWith");b+="";var e=d.length,f=b.length;c=Math.max(0,Math.min(c|0,d.length));for(var g=0;g<f&&c<e;)if(d[c++]!=b[g++])return!1;return g>=f}});
function La(a,b){a instanceof String&&(a+="");var c=0,d=!1,e={next:function(){if(!d&&c<a.length){var f=c++;return{value:b(f,a[f]),done:!1}}d=!0;return{done:!0,value:void 0}}};
e[Symbol.iterator]=function(){return e};
return e}
n("Array.prototype.entries",function(a){return a?a:function(){return La(this,function(b,c){return[b,c]})}});
n("Object.setPrototypeOf",function(a){return a||qa});
n("Set",function(a){function b(c){this.h=new Map;if(c){c=p(c);for(var d;!(d=c.next()).done;)this.add(d.value)}this.size=this.h.size}
if(function(){if(!a||"function"!=typeof a||!a.prototype.entries||"function"!=typeof Object.seal)return!1;try{var c=Object.seal({x:4}),d=new a(p([c]));if(!d.has(c)||1!=d.size||d.add(c)!=d||1!=d.size||d.add({x:4})!=d||2!=d.size)return!1;var e=d.entries(),f=e.next();if(f.done||f.value[0]!=c||f.value[1]!=c)return!1;f=e.next();return f.done||f.value[0]==c||4!=f.value[0].x||f.value[1]!=f.value[0]?!1:e.next().done}catch(g){return!1}}())return a;
b.prototype.add=function(c){c=0===c?0:c;this.h.set(c,c);this.size=this.h.size;return this};
b.prototype.delete=function(c){c=this.h.delete(c);this.size=this.h.size;return c};
b.prototype.clear=function(){this.h.clear();this.size=0};
b.prototype.has=function(c){return this.h.has(c)};
b.prototype.entries=function(){return this.h.entries()};
b.prototype.values=function(){return this.h.values()};
b.prototype.keys=b.prototype.values;b.prototype[Symbol.iterator]=b.prototype.values;b.prototype.forEach=function(c,d){var e=this;this.h.forEach(function(f){return c.call(d,f,f,e)})};
return b});
n("Object.entries",function(a){return a?a:function(b){var c=[],d;for(d in b)ha(b,d)&&c.push([d,b[d]]);return c}});
n("Array.prototype.keys",function(a){return a?a:function(){return La(this,function(b){return b})}});
n("Array.prototype.values",function(a){return a?a:function(){return La(this,function(b,c){return c})}});
n("Object.is",function(a){return a?a:function(b,c){return b===c?0!==b||1/b===1/c:b!==b&&c!==c}});
n("Array.prototype.includes",function(a){return a?a:function(b,c){var d=this;d instanceof String&&(d=String(d));var e=d.length;c=c||0;for(0>c&&(c=Math.max(c+e,0));c<e;c++){var f=d[c];if(f===b||Object.is(f,b))return!0}return!1}});
n("String.prototype.includes",function(a){return a?a:function(b,c){return-1!==Ka(this,b,"includes").indexOf(b,c||0)}});
n("Array.from",function(a){return a?a:function(b,c,d){c=null!=c?c:function(h){return h};
var e=[],f="undefined"!=typeof Symbol&&Symbol.iterator&&b[Symbol.iterator];if("function"==typeof f){b=f.call(b);for(var g=0;!(f=b.next()).done;)e.push(c.call(d,f.value,g++))}else for(f=b.length,g=0;g<f;g++)e.push(c.call(d,b[g],g));return e}});
n("Number.isNaN",function(a){return a?a:function(b){return"number"===typeof b&&isNaN(b)}});
n("Number.MAX_SAFE_INTEGER",function(){return 9007199254740991});
n("Object.values",function(a){return a?a:function(b){var c=[],d;for(d in b)ha(b,d)&&c.push(b[d]);return c}});
var x=this||self;function y(a,b,c){a=a.split(".");c=c||x;a[0]in c||"undefined"==typeof c.execScript||c.execScript("var "+a[0]);for(var d;a.length&&(d=a.shift());)a.length||void 0===b?c[d]&&c[d]!==Object.prototype[d]?c=c[d]:c=c[d]={}:c[d]=b}
function z(a,b){a=a.split(".");b=b||x;for(var c=0;c<a.length;c++)if(b=b[a[c]],null==b)return null;return b}
function Ma(){}
function Na(a){a.cb=void 0;a.getInstance=function(){return a.cb?a.cb:a.cb=new a}}
function Pa(a){var b=typeof a;return"object"!=b?b:a?Array.isArray(a)?"array":b:"null"}
function Qa(a){var b=Pa(a);return"array"==b||"object"==b&&"number"==typeof a.length}
function Ra(a){var b=typeof a;return"object"==b&&null!=a||"function"==b}
function Sa(a){return Object.prototype.hasOwnProperty.call(a,Ta)&&a[Ta]||(a[Ta]=++Ua)}
var Ta="closure_uid_"+(1E9*Math.random()>>>0),Ua=0;function Va(a,b,c){return a.call.apply(a.bind,arguments)}
function Wa(a,b,c){if(!a)throw Error();if(2<arguments.length){var d=Array.prototype.slice.call(arguments,2);return function(){var e=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(e,d);return a.apply(b,e)}}return function(){return a.apply(b,arguments)}}
function Xa(a,b,c){Function.prototype.bind&&-1!=Function.prototype.bind.toString().indexOf("native code")?Xa=Va:Xa=Wa;return Xa.apply(null,arguments)}
function Ya(a,b){var c=Array.prototype.slice.call(arguments,1);return function(){var d=c.slice();d.push.apply(d,arguments);return a.apply(this,d)}}
function Za(a,b){y(a,b,void 0)}
function $a(a,b){function c(){}
c.prototype=b.prototype;a.aa=b.prototype;a.prototype=new c;a.prototype.constructor=a;a.No=function(d,e,f){for(var g=Array(arguments.length-2),h=2;h<arguments.length;h++)g[h-2]=arguments[h];return b.prototype[e].apply(d,g)}}
function ab(a){return a}
;function bb(a,b){if(Error.captureStackTrace)Error.captureStackTrace(this,bb);else{var c=Error().stack;c&&(this.stack=c)}a&&(this.message=String(a));void 0!==b&&(this.Pb=b)}
$a(bb,Error);bb.prototype.name="CustomError";function cb(a){a=a.url;var b=/[?&]dsh=1(&|$)/.test(a);this.j=!b&&/[?&]ae=1(&|$)/.test(a);this.l=!b&&/[?&]ae=2(&|$)/.test(a);if((this.h=/[?&]adurl=([^&]*)/.exec(a))&&this.h[1]){try{var c=decodeURIComponent(this.h[1])}catch(d){c=null}this.i=c}}
;function db(){}
function eb(a){var b=!1,c;return function(){b||(c=a(),b=!0);return c}}
;var fb=Array.prototype.indexOf?function(a,b){return Array.prototype.indexOf.call(a,b,void 0)}:function(a,b){if("string"===typeof a)return"string"!==typeof b||1!=b.length?-1:a.indexOf(b,0);
for(var c=0;c<a.length;c++)if(c in a&&a[c]===b)return c;return-1},gb=Array.prototype.forEach?function(a,b,c){Array.prototype.forEach.call(a,b,c)}:function(a,b,c){for(var d=a.length,e="string"===typeof a?a.split(""):a,f=0;f<d;f++)f in e&&b.call(c,e[f],f,a)},hb=Array.prototype.filter?function(a,b){return Array.prototype.filter.call(a,b,void 0)}:function(a,b){for(var c=a.length,d=[],e=0,f="string"===typeof a?a.split(""):a,g=0;g<c;g++)if(g in f){var h=f[g];
b.call(void 0,h,g,a)&&(d[e++]=h)}return d},ib=Array.prototype.map?function(a,b){return Array.prototype.map.call(a,b,void 0)}:function(a,b){for(var c=a.length,d=Array(c),e="string"===typeof a?a.split(""):a,f=0;f<c;f++)f in e&&(d[f]=b.call(void 0,e[f],f,a));
return d},jb=Array.prototype.reduce?function(a,b,c){return Array.prototype.reduce.call(a,b,c)}:function(a,b,c){var d=c;
gb(a,function(e,f){d=b.call(void 0,d,e,f,a)});
return d};
function kb(a,b){a:{for(var c=a.length,d="string"===typeof a?a.split(""):a,e=0;e<c;e++)if(e in d&&b.call(void 0,d[e],e,a)){b=e;break a}b=-1}return 0>b?null:"string"===typeof a?a.charAt(b):a[b]}
function lb(a,b){b=fb(a,b);var c;(c=0<=b)&&Array.prototype.splice.call(a,b,1);return c}
function mb(a,b){for(var c=1;c<arguments.length;c++){var d=arguments[c];if(Qa(d)){var e=a.length||0,f=d.length||0;a.length=e+f;for(var g=0;g<f;g++)a[e+g]=d[g]}else a.push(d)}}
;function nb(a,b){for(var c in a)b.call(void 0,a[c],c,a)}
function ob(a){var b=pb,c;for(c in b)if(a.call(void 0,b[c],c,b))return c}
function qb(a){for(var b in a)return!1;return!0}
function tb(a,b){if(null!==a&&b in a)throw Error('The object already contains the key "'+b+'"');a[b]=!0}
function ub(){var a=A("PLAYER_VARS",{});return null!==a&&"privembed"in a?a.privembed:!1}
function vb(a,b){for(var c in a)if(!(c in b)||a[c]!==b[c])return!1;for(var d in b)if(!(d in a))return!1;return!0}
function wb(a){var b={},c;for(c in a)b[c]=a[c];return b}
function xb(a){if(!a||"object"!==typeof a)return a;if("function"===typeof a.clone)return a.clone();if("undefined"!==typeof Map&&a instanceof Map)return new Map(a);if("undefined"!==typeof Set&&a instanceof Set)return new Set(a);var b=Array.isArray(a)?[]:"function"!==typeof ArrayBuffer||"function"!==typeof ArrayBuffer.isView||!ArrayBuffer.isView(a)||a instanceof DataView?{}:new a.constructor(a.length),c;for(c in a)b[c]=xb(a[c]);return b}
var yb="constructor hasOwnProperty isPrototypeOf propertyIsEnumerable toLocaleString toString valueOf".split(" ");function zb(a,b){for(var c,d,e=1;e<arguments.length;e++){d=arguments[e];for(c in d)a[c]=d[c];for(var f=0;f<yb.length;f++)c=yb[f],Object.prototype.hasOwnProperty.call(d,c)&&(a[c]=d[c])}}
;var Ab;function Bb(){if(void 0===Ab){var a=null,b=x.trustedTypes;if(b&&b.createPolicy){try{a=b.createPolicy("goog#html",{createHTML:ab,createScript:ab,createScriptURL:ab})}catch(c){x.console&&x.console.error(c.message)}Ab=a}else Ab=a}return Ab}
;function Cb(a,b){this.j=a===Db&&b||""}
Cb.prototype.i=!0;Cb.prototype.h=function(){return this.j};
function Eb(a){return new Cb(Db,a)}
var Db={};Eb("");var Fb={};function Gb(a){this.j=Fb===Fb?a:"";this.i=!0}
Gb.prototype.h=function(){return this.j.toString()};
Gb.prototype.toString=function(){return this.j.toString()};function Hb(a,b){this.j=b===Ib?a:""}
Hb.prototype.i=!0;Hb.prototype.h=function(){return this.j.toString()};
Hb.prototype.toString=function(){return this.j+""};
function Jb(a){if(a instanceof Hb&&a.constructor===Hb)return a.j;Pa(a);return"type_error:TrustedResourceUrl"}
var Ib={};function Kb(a){var b=Bb();a=b?b.createScriptURL(a):a;return new Hb(a,Ib)}
;var Lb=String.prototype.trim?function(a){return a.trim()}:function(a){return/^[\s\xa0]*([\s\S]*?)[\s\xa0]*$/.exec(a)[1]};function Ob(a,b){this.j=b===Pb?a:""}
Ob.prototype.i=!0;Ob.prototype.h=function(){return this.j.toString()};
Ob.prototype.toString=function(){return this.j.toString()};
function Qb(a){if(a instanceof Ob&&a.constructor===Ob)return a.j;Pa(a);return"type_error:SafeUrl"}
var Rb=/^(?:(?:https?|mailto|ftp):|[^:/?#]*(?:[/?#]|$))/i,Pb={};function Sb(){var a=x.navigator;return a&&(a=a.userAgent)?a:""}
function B(a){return-1!=Sb().indexOf(a)}
;function Tb(){return(B("Chrome")||B("CriOS"))&&!B("Edge")||B("Silk")}
;var Ub={};function Vb(a){this.j=Ub===Ub?a:"";this.i=!0}
Vb.prototype.h=function(){return this.j.toString()};
Vb.prototype.toString=function(){return this.j.toString()};function Wb(a,b){b instanceof Ob||b instanceof Ob||(b="object"==typeof b&&b.i?b.h():String(b),Rb.test(b)||(b="about:invalid#zClosurez"),b=new Ob(b,Pb));a.href=Qb(b)}
function Xb(a,b){a.rel="stylesheet";a.href=Jb(b).toString();(b=Yb('style[nonce],link[rel="stylesheet"][nonce]',a.ownerDocument&&a.ownerDocument.defaultView))&&a.setAttribute("nonce",b)}
function Zb(){return Yb("script[nonce]",void 0)}
var $b=/^[\w+/_-]+[=]{0,2}$/;function Yb(a,b){b=(b||x).document;return b.querySelector?(a=b.querySelector(a))&&(a=a.nonce||a.getAttribute("nonce"))&&$b.test(a)?a:"":""}
;function ac(a){for(var b=0,c=0;c<a.length;++c)b=31*b+a.charCodeAt(c)>>>0;return b}
;var bc=RegExp("^(?:([^:/?#.]+):)?(?://(?:([^\\\\/?#]*)@)?([^\\\\/?#]*?)(?::([0-9]+))?(?=[\\\\/?#]|$))?([^?#]+)?(?:\\?([^#]*))?(?:#([\\s\\S]*))?$");function cc(a){return a?decodeURI(a):a}
function dc(a,b){return b.match(bc)[a]||null}
function ec(a){return cc(dc(3,a))}
function fc(a){var b=a.match(bc);a=b[5];var c=b[6];b=b[7];var d="";a&&(d+=a);c&&(d+="?"+c);b&&(d+="#"+b);return d}
function gc(a,b,c){if(Array.isArray(b))for(var d=0;d<b.length;d++)gc(a,String(b[d]),c);else null!=b&&c.push(a+(""===b?"":"="+encodeURIComponent(String(b))))}
function hc(a){var b=[],c;for(c in a)gc(c,a[c],b);return b.join("&")}
function ic(a,b){b=hc(b);if(b){var c=a.indexOf("#");0>c&&(c=a.length);var d=a.indexOf("?");if(0>d||d>c){d=c;var e=""}else e=a.substring(d+1,c);a=[a.substr(0,d),e,a.substr(c)];c=a[1];a[1]=b?c?c+"&"+b:b:c;b=a[0]+(a[1]?"?"+a[1]:"")+a[2]}else b=a;return b}
function jc(a,b,c,d){for(var e=c.length;0<=(b=a.indexOf(c,b))&&b<d;){var f=a.charCodeAt(b-1);if(38==f||63==f)if(f=a.charCodeAt(b+e),!f||61==f||38==f||35==f)return b;b+=e+1}return-1}
var kc=/#|$/,oc=/[?&]($|#)/;function pc(a){for(var b=a.search(kc),c=0,d,e=[];0<=(d=jc(a,c,"key",b));)e.push(a.substring(c,d)),c=Math.min(a.indexOf("&",d)+1||b,b);e.push(a.substr(c));return e.join("").replace(oc,"$1")}
;function qc(){return B("iPhone")&&!B("iPod")&&!B("iPad")}
;function rc(a){rc[" "](a);return a}
rc[" "]=Ma;var sc=B("Opera"),tc=B("Trident")||B("MSIE"),uc=B("Edge"),vc=B("Gecko")&&!(-1!=Sb().toLowerCase().indexOf("webkit")&&!B("Edge"))&&!(B("Trident")||B("MSIE"))&&!B("Edge"),wc=-1!=Sb().toLowerCase().indexOf("webkit")&&!B("Edge"),xc=B("Android");function yc(){var a=x.document;return a?a.documentMode:void 0}
var zc;a:{var Ac="",Bc=function(){var a=Sb();if(vc)return/rv:([^\);]+)(\)|;)/.exec(a);if(uc)return/Edge\/([\d\.]+)/.exec(a);if(tc)return/\b(?:MSIE|rv)[: ]([^\);]+)(\)|;)/.exec(a);if(wc)return/WebKit\/(\S+)/.exec(a);if(sc)return/(?:Version)[ \/]?(\S+)/.exec(a)}();
Bc&&(Ac=Bc?Bc[1]:"");if(tc){var Cc=yc();if(null!=Cc&&Cc>parseFloat(Ac)){zc=String(Cc);break a}}zc=Ac}var Dc=zc,Ec;if(x.document&&tc){var Fc=yc();Ec=Fc?Fc:parseInt(Dc,10)||void 0}else Ec=void 0;var Gc=Ec;var Hc=qc()||B("iPod"),Ic=B("iPad");!B("Android")||Tb();Tb();var Jc=B("Safari")&&!(Tb()||B("Coast")||B("Opera")||B("Edge")||B("Edg/")||B("OPR")||B("Firefox")||B("FxiOS")||B("Silk")||B("Android"))&&!(qc()||B("iPad")||B("iPod"));var Kc={},Lc=null;
function Mc(a,b){Qa(a);void 0===b&&(b=0);if(!Lc){Lc={};for(var c="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789".split(""),d=["+/=","+/","-_=","-_.","-_"],e=0;5>e;e++){var f=c.concat(d[e].split(""));Kc[e]=f;for(var g=0;g<f.length;g++){var h=f[g];void 0===Lc[h]&&(Lc[h]=g)}}}b=Kc[b];c=Array(Math.floor(a.length/3));d=b[64]||"";for(e=f=0;f<a.length-2;f+=3){var k=a[f],m=a[f+1];h=a[f+2];g=b[k>>2];k=b[(k&3)<<4|m>>4];m=b[(m&15)<<2|h>>6];h=b[h&63];c[e++]=""+g+k+m+h}g=0;h=d;switch(a.length-
f){case 2:g=a[f+1],h=b[(g&15)<<2]||d;case 1:a=a[f],c[e]=""+b[a>>2]+b[(a&3)<<4|g>>4]+h+d}return c.join("")}
;var Nc="undefined"!==typeof Uint8Array;var Oc="function"===typeof Symbol&&"symbol"===typeof Symbol()?Symbol(void 0):void 0;function Pc(a,b){Object.isFrozen(a)||(Oc?a[Oc]|=b:void 0!==a.Ma?a.Ma|=b:Object.defineProperties(a,{Ma:{value:b,configurable:!0,writable:!0,enumerable:!1}}))}
function Qc(a){var b;Oc?b=a[Oc]:b=a.Ma;return null==b?0:b}
function Rc(a){Pc(a,1);return a}
function Sc(a){return Array.isArray(a)?!!(Qc(a)&2):!1}
function Tc(a){if(!Array.isArray(a))throw Error("cannot mark non-array as immutable");Pc(a,2)}
;function Uc(a){return null!==a&&"object"===typeof a&&!Array.isArray(a)&&a.constructor===Object}
var Vc,Wc=Object.freeze(Rc([]));function Xc(a){if(Sc(a.G))throw Error("Cannot mutate an immutable Message");}
var Yc="undefined"!=typeof Symbol&&"undefined"!=typeof Symbol.hasInstance;function Zc(a){return{value:a,configurable:!1,writable:!1,enumerable:!1}}
;function $c(a){switch(typeof a){case "number":return isFinite(a)?a:String(a);case "object":if(a&&!Array.isArray(a)&&Nc&&null!=a&&a instanceof Uint8Array)return Mc(a)}return a}
;function dd(a,b){b=void 0===b?ed:b;return fd(a,b)}
function gd(a,b){if(null!=a){if(Array.isArray(a))a=fd(a,b);else if(Uc(a)){var c={},d;for(d in a)c[d]=gd(a[d],b);a=c}else a=b(a);return a}}
function fd(a,b){for(var c=a.slice(),d=0;d<c.length;d++)c[d]=gd(c[d],b);Array.isArray(a)&&Qc(a)&1&&Rc(c);return c}
function hd(a){if(a&&"object"==typeof a&&a.toJSON)return a.toJSON();a=$c(a);return Array.isArray(a)?dd(a,hd):a}
function ed(a){return Nc&&null!=a&&a instanceof Uint8Array?new Uint8Array(a):a}
;function id(a,b,c){return-1===b?null:b>=a.l?a.i?a.i[b]:void 0:(void 0===c?0:c)&&a.i&&(c=a.i[b],null!=c)?c:a.G[b+a.j]}
function D(a,b,c,d,e){d=void 0===d?!1:d;(void 0===e?0:e)||Xc(a);b<a.l&&!d?a.G[b+a.j]=c:(a.i||(a.i=a.G[a.l+a.j]={}))[b]=c;return a}
function jd(a,b,c,d){c=void 0===c?!0:c;d=void 0===d?!1:d;var e=id(a,b,d);null==e&&(e=Wc);if(Sc(a.G))c&&(Tc(e),Object.freeze(e));else if(e===Wc||Sc(e))e=Rc(e.slice()),D(a,b,e,d);return e}
function kd(a,b,c,d){Xc(a);(c=ld(a,c))&&c!==b&&null!=d&&(a.h&&c in a.h&&(a.h[c]=void 0),D(a,c,void 0));return D(a,b,d)}
function ld(a,b){for(var c=0,d=0;d<b.length;d++){var e=b[d];null!=id(a,e)&&(0!==c&&D(a,c,void 0,!1,!0),c=e)}return c}
function md(a,b,c,d,e){if(-1===c)return null;a.h||(a.h={});var f=a.h[c];if(f)return f;e=id(a,c,void 0===e?!1:e);if(null==e&&!d)return f;b=new b(e);Sc(a.G)&&Tc(b.G);return a.h[c]=b}
function nd(a,b,c,d){d=void 0===d?!1:d;a.h||(a.h={});var e=Sc(a.G),f=a.h[c];if(!f){d=jd(a,c,!0,d);f=[];e=e||Sc(d);for(var g=0;g<d.length;g++)f[g]=new b(d[g]),e&&Tc(f[g].G);e&&(Tc(f),Object.freeze(f));a.h[c]=f}return f}
function I(a,b,c,d){d=void 0===d?!1:d;Xc(a);a.h||(a.h={});var e=c?c.G:c;a.h[b]=c;return D(a,b,e,d)}
function od(a,b,c,d){Xc(a);a.h||(a.h={});var e=d?d.G:d;a.h[b]=d;kd(a,b,c,e)}
function pd(a,b,c,d){var e=void 0===e?!1:e;Xc(a);e=nd(a,c,b,e);c=d?d:new c;a=jd(a,b);e.push(c);a.push(c.G)}
function qd(a,b){a=id(a,b);return null==a?"":a}
;function rd(a,b,c){a||(a=sd);sd=null;var d=this.constructor.i;a||(a=d?[d]:[]);this.j=(d?0:-1)-(this.constructor.h||0);this.h=void 0;this.G=a;a:{d=this.G.length;a=d-1;if(d&&(d=this.G[a],Uc(d))){this.l=a-this.j;this.i=d;break a}void 0!==b&&-1<b?(this.l=Math.max(b,a+1-this.j),this.i=void 0):this.l=Number.MAX_VALUE}if(c)for(b=0;b<c.length;b++)if(a=c[b],a<this.l)a+=this.j,(d=this.G[a])?Array.isArray(d)&&Rc(d):this.G[a]=Wc;else{d=this.i||(this.i=this.G[this.l+this.j]={});var e=d[a];e?Array.isArray(e)&&
Rc(e):d[a]=Wc}}
rd.prototype.toJSON=function(){var a=this.G;return Vc?a:dd(a,hd)};
function td(a){Vc=!0;try{return JSON.stringify(a.toJSON(),ud)}finally{Vc=!1}}
rd.prototype.clone=function(){var a=dd(this.G);sd=a;a=new this.constructor(a);sd=null;vd(a,this);return a};
rd.prototype.toString=function(){return this.G.toString()};
function ud(a,b){return $c(b)}
function vd(a,b){b.o&&(a.o=b.o.slice());var c=b.h;if(c){b=b.i;for(var d in c){var e=c[d];if(e){var f=!(!b||!b[d]),g=+d;if(Array.isArray(e)){if(e.length)for(f=nd(a,e[0].constructor,g,f),g=0;g<Math.min(f.length,e.length);g++)vd(f[g],e[g])}else(f=md(a,e.constructor,g,void 0,f))&&vd(f,e)}}}}
var sd;function wd(){rd.apply(this,arguments)}
r(wd,rd);if(Yc){var xd={};Object.defineProperties(wd,(xd[Symbol.hasInstance]=Zc(function(){throw Error("Cannot perform instanceof checks for MutableMessage");}),xd))};function yd(a,b){var c=this.h;if(this.isRepeated){var d=!0;d=void 0===d?!1:d;Xc(a);if(b){var e=Rc([]);for(var f=0;f<b.length;f++)e[f]=b[f].G;a.h||(a.h={});a.h[c]=b}else a.h&&(a.h[c]=void 0),e=Wc;a=D(a,c,e,d)}else a=I(a,c,b,!0);return a}
;function J(){wd.apply(this,arguments)}
r(J,wd);if(Yc){var zd={};Object.defineProperties(J,(zd[Symbol.hasInstance]=Zc(Object[Symbol.hasInstance]),zd))};function Ad(){var a=this;this.promise=new Promise(function(b,c){a.resolve=b;a.reject=c})}
;function Bd(a){this.i=!1;var b=a.program;a=a.globalName;var c=new Ad;this.j=c.promise;this.l=p((0,x[a].a)(b,function(d,e){Promise.resolve().then(function(){c.resolve({Ob:d,xc:e})})},!0)).next().value;
this.wc=c.promise.then(function(){})}
Bd.prototype.snapshot=function(a){if(this.i)throw Error("Already disposed");return this.j.then(function(b){var c=b.Ob;return new Promise(function(d){c(function(e){d(e)},[a.pb,
a.yc])})})};
Bd.prototype.dispose=function(){this.i=!0;this.j.then(function(a){(a=a.xc)&&a()})};
Bd.prototype.h=function(){return this.i};var Cd=window;Eb("csi.gstatic.com");Eb("googleads.g.doubleclick.net");Eb("partner.googleadservices.com");Eb("pubads.g.doubleclick.net");Eb("securepubads.g.doubleclick.net");Eb("tpc.googlesyndication.com");/*

 SPDX-License-Identifier: Apache-2.0
*/
var Dd={};function Ed(){}
function Fd(a){this.h=a}
r(Fd,Ed);Fd.prototype.toString=function(){return this.h};
var Gd=new Fd("about:invalid#zTSz",Dd);function Hd(a){if(a instanceof Ed)if(a instanceof Fd)a=a.h;else throw Error("");else a=Qb(a);return a}
;function Id(a,b){a.src=Jb(b);var c,d;(c=(b=null==(d=(c=(a.ownerDocument&&a.ownerDocument.defaultView||window).document).querySelector)?void 0:d.call(c,"script[nonce]"))?b.nonce||b.getAttribute("nonce")||"":"")&&a.setAttribute("nonce",c)}
;function Jd(a,b){this.x=void 0!==a?a:0;this.y=void 0!==b?b:0}
l=Jd.prototype;l.clone=function(){return new Jd(this.x,this.y)};
l.equals=function(a){return a instanceof Jd&&(this==a?!0:this&&a?this.x==a.x&&this.y==a.y:!1)};
l.ceil=function(){this.x=Math.ceil(this.x);this.y=Math.ceil(this.y);return this};
l.floor=function(){this.x=Math.floor(this.x);this.y=Math.floor(this.y);return this};
l.round=function(){this.x=Math.round(this.x);this.y=Math.round(this.y);return this};
l.scale=function(a,b){this.x*=a;this.y*="number"===typeof b?b:a;return this};function Kd(a,b){this.width=a;this.height=b}
l=Kd.prototype;l.clone=function(){return new Kd(this.width,this.height)};
l.aspectRatio=function(){return this.width/this.height};
l.isEmpty=function(){return!(this.width*this.height)};
l.ceil=function(){this.width=Math.ceil(this.width);this.height=Math.ceil(this.height);return this};
l.floor=function(){this.width=Math.floor(this.width);this.height=Math.floor(this.height);return this};
l.round=function(){this.width=Math.round(this.width);this.height=Math.round(this.height);return this};
l.scale=function(a,b){this.width*=a;this.height*="number"===typeof b?b:a;return this};function Ld(a){var b=document;return"string"===typeof a?b.getElementById(a):a}
function Md(a){var b=document;a=String(a);"application/xhtml+xml"===b.contentType&&(a=a.toLowerCase());return b.createElement(a)}
function Nd(a,b){for(var c=0;a;){if(b(a))return a;a=a.parentNode;c++}return null}
;function Od(a){var b=Pd;if(b)for(var c in b)Object.prototype.hasOwnProperty.call(b,c)&&a(b[c],c,b)}
function Qd(){var a=[];Od(function(b){a.push(b)});
return a}
var Pd={Pc:"allow-forms",Qc:"allow-modals",Rc:"allow-orientation-lock",Sc:"allow-pointer-lock",Tc:"allow-popups",Uc:"allow-popups-to-escape-sandbox",Vc:"allow-presentation",Wc:"allow-same-origin",Xc:"allow-scripts",Yc:"allow-top-navigation",Zc:"allow-top-navigation-by-user-activation"},Rd=eb(function(){return Qd()});
function Sd(){var a=Td(),b={};gb(Rd(),function(c){a.sandbox&&a.sandbox.supports&&a.sandbox.supports(c)&&(b[c]=!0)});
return b}
function Td(){var a=void 0===a?document:a;return a.createElement("iframe")}
;function Ud(a){this.isValid=a}
function Vd(a){return new Ud(function(b){return b.substr(0,a.length+1).toLowerCase()===a+":"})}
var Wd=[Vd("data"),Vd("http"),Vd("https"),Vd("mailto"),Vd("ftp"),new Ud(function(a){return/^[^:]*([/?#]|$)/.test(a)})];function Xd(a){"number"==typeof a&&(a=Math.round(a)+"px");return a}
;var Yd=(new Date).getTime();function Zd(a){if(!a)return"";if(/^about:(?:blank|srcdoc)$/.test(a))return window.origin||"";a=a.split("#")[0].split("?")[0];a=a.toLowerCase();0==a.indexOf("//")&&(a=window.location.protocol+a);/^[\w\-]*:\/\//.test(a)||(a=window.location.href);var b=a.substring(a.indexOf("://")+3),c=b.indexOf("/");-1!=c&&(b=b.substring(0,c));c=a.substring(0,a.indexOf("://"));if(!c)throw Error("URI is missing protocol: "+a);if("http"!==c&&"https"!==c&&"chrome-extension"!==c&&"moz-extension"!==c&&"file"!==c&&"android-app"!==
c&&"chrome-search"!==c&&"chrome-untrusted"!==c&&"chrome"!==c&&"app"!==c&&"devtools"!==c)throw Error("Invalid URI scheme in origin: "+c);a="";var d=b.indexOf(":");if(-1!=d){var e=b.substring(d+1);b=b.substring(0,d);if("http"===c&&"80"!==e||"https"===c&&"443"!==e)a=":"+e}return c+"://"+b+a}
;function ce(){function a(){e[0]=1732584193;e[1]=4023233417;e[2]=2562383102;e[3]=271733878;e[4]=3285377520;q=m=0}
function b(u){for(var C=g,v=0;64>v;v+=4)C[v/4]=u[v]<<24|u[v+1]<<16|u[v+2]<<8|u[v+3];for(v=16;80>v;v++)u=C[v-3]^C[v-8]^C[v-14]^C[v-16],C[v]=(u<<1|u>>>31)&4294967295;u=e[0];var E=e[1],F=e[2],H=e[3],R=e[4];for(v=0;80>v;v++){if(40>v)if(20>v){var O=H^E&(F^H);var S=1518500249}else O=E^F^H,S=1859775393;else 60>v?(O=E&F|H&(E|F),S=2400959708):(O=E^F^H,S=3395469782);O=((u<<5|u>>>27)&4294967295)+O+R+S+C[v]&4294967295;R=H;H=F;F=(E<<30|E>>>2)&4294967295;E=u;u=O}e[0]=e[0]+u&4294967295;e[1]=e[1]+E&4294967295;e[2]=
e[2]+F&4294967295;e[3]=e[3]+H&4294967295;e[4]=e[4]+R&4294967295}
function c(u,C){if("string"===typeof u){u=unescape(encodeURIComponent(u));for(var v=[],E=0,F=u.length;E<F;++E)v.push(u.charCodeAt(E));u=v}C||(C=u.length);v=0;if(0==m)for(;v+64<C;)b(u.slice(v,v+64)),v+=64,q+=64;for(;v<C;)if(f[m++]=u[v++],q++,64==m)for(m=0,b(f);v+64<C;)b(u.slice(v,v+64)),v+=64,q+=64}
function d(){var u=[],C=8*q;56>m?c(h,56-m):c(h,64-(m-56));for(var v=63;56<=v;v--)f[v]=C&255,C>>>=8;b(f);for(v=C=0;5>v;v++)for(var E=24;0<=E;E-=8)u[C++]=e[v]>>E&255;return u}
for(var e=[],f=[],g=[],h=[128],k=1;64>k;++k)h[k]=0;var m,q;a();return{reset:a,update:c,digest:d,Sb:function(){for(var u=d(),C="",v=0;v<u.length;v++)C+="0123456789ABCDEF".charAt(Math.floor(u[v]/16))+"0123456789ABCDEF".charAt(u[v]%16);return C}}}
;function de(a,b,c){var d=String(x.location.href);return d&&a&&b?[b,ee(Zd(d),a,c||null)].join(" "):null}
function ee(a,b,c){var d=[],e=[];if(1==(Array.isArray(c)?2:1))return e=[b,a],gb(d,function(h){e.push(h)}),fe(e.join(" "));
var f=[],g=[];gb(c,function(h){g.push(h.key);f.push(h.value)});
c=Math.floor((new Date).getTime()/1E3);e=0==f.length?[c,b,a]:[f.join(":"),c,b,a];gb(d,function(h){e.push(h)});
a=fe(e.join(" "));a=[c,a];0==g.length||a.push(g.join(""));return a.join("_")}
function fe(a){var b=ce();b.update(a);return b.Sb().toLowerCase()}
;var ge={};function he(a){this.h=a||{cookie:""}}
l=he.prototype;l.isEnabled=function(){if(!x.navigator.cookieEnabled)return!1;if(!this.isEmpty())return!0;this.set("TESTCOOKIESENABLED","1",{Oa:60});if("1"!==this.get("TESTCOOKIESENABLED"))return!1;this.remove("TESTCOOKIESENABLED");return!0};
l.set=function(a,b,c){var d=!1;if("object"===typeof c){var e=c.Zo;d=c.secure||!1;var f=c.domain||void 0;var g=c.path||void 0;var h=c.Oa}if(/[;=\s]/.test(a))throw Error('Invalid cookie name "'+a+'"');if(/[;\r\n]/.test(b))throw Error('Invalid cookie value "'+b+'"');void 0===h&&(h=-1);c=f?";domain="+f:"";g=g?";path="+g:"";d=d?";secure":"";h=0>h?"":0==h?";expires="+(new Date(1970,1,1)).toUTCString():";expires="+(new Date(Date.now()+1E3*h)).toUTCString();this.h.cookie=a+"="+b+c+g+h+d+(null!=e?";samesite="+
e:"")};
l.get=function(a,b){for(var c=a+"=",d=(this.h.cookie||"").split(";"),e=0,f;e<d.length;e++){f=Lb(d[e]);if(0==f.lastIndexOf(c,0))return f.substr(c.length);if(f==a)return""}return b};
l.remove=function(a,b,c){var d=void 0!==this.get(a);this.set(a,"",{Oa:0,path:b,domain:c});return d};
l.Ya=function(){return ie(this).keys};
l.isEmpty=function(){return!this.h.cookie};
l.clear=function(){for(var a=ie(this).keys,b=a.length-1;0<=b;b--)this.remove(a[b])};
function ie(a){a=(a.h.cookie||"").split(";");for(var b=[],c=[],d,e,f=0;f<a.length;f++)e=Lb(a[f]),d=e.indexOf("="),-1==d?(b.push(""),c.push(e)):(b.push(e.substring(0,d)),c.push(e.substring(d+1)));return{keys:b,values:c}}
var je=new he("undefined"==typeof document?null:document);function ke(a){return!!ge.FPA_SAMESITE_PHASE2_MOD||!(void 0===a||!a)}
function le(a){a=void 0===a?!1:a;var b=x.__SAPISID||x.__APISID||x.__3PSAPISID||x.__OVERRIDE_SID;ke(a)&&(b=b||x.__1PSAPISID);if(b)return!0;var c=new he(document);b=c.get("SAPISID")||c.get("APISID")||c.get("__Secure-3PAPISID")||c.get("SID");ke(a)&&(b=b||c.get("__Secure-1PAPISID"));return!!b}
function me(a,b,c,d){(a=x[a])||(a=(new he(document)).get(b));return a?de(a,c,d):null}
function ne(a){var b=void 0===b?!1:b;var c=Zd(String(x.location.href)),d=[];if(le(b)){c=0==c.indexOf("https:")||0==c.indexOf("chrome-extension:")||0==c.indexOf("moz-extension:");var e=c?x.__SAPISID:x.__APISID;e||(e=new he(document),e=e.get(c?"SAPISID":"APISID")||e.get("__Secure-3PAPISID"));(e=e?de(e,c?"SAPISIDHASH":"APISIDHASH",a):null)&&d.push(e);c&&ke(b)&&((b=me("__1PSAPISID","__Secure-1PAPISID","SAPISID1PHASH",a))&&d.push(b),(a=me("__3PSAPISID","__Secure-3PAPISID","SAPISID3PHASH",a))&&d.push(a))}return 0==
d.length?null:d.join(" ")}
;function oe(a){if(Yc){var b={};Object.defineProperties(a,(b[Symbol.hasInstance]=Zc(Object[Symbol.hasInstance]),b))}}
;function pe(a){a&&"function"==typeof a.dispose&&a.dispose()}
;function qe(a){for(var b=0,c=arguments.length;b<c;++b){var d=arguments[b];Qa(d)?qe.apply(null,d):pe(d)}}
;function K(){this.C=this.C;this.o=this.o}
K.prototype.C=!1;K.prototype.h=function(){return this.C};
K.prototype.dispose=function(){this.C||(this.C=!0,this.I())};
function re(a,b){a.C?b():(a.o||(a.o=[]),a.o.push(b))}
K.prototype.I=function(){if(this.o)for(;this.o.length;)this.o.shift()()};function se(a,b){this.type=a;this.h=this.target=b;this.defaultPrevented=this.j=!1}
se.prototype.stopPropagation=function(){this.j=!0};
se.prototype.preventDefault=function(){this.defaultPrevented=!0};function te(a){var b=z("window.location.href");null==a&&(a='Unknown Error of type "null/undefined"');if("string"===typeof a)return{message:a,name:"Unknown error",lineNumber:"Not available",fileName:b,stack:"Not available"};var c=!1;try{var d=a.lineNumber||a.line||"Not available"}catch(g){d="Not available",c=!0}try{var e=a.fileName||a.filename||a.sourceURL||x.$googDebugFname||b}catch(g){e="Not available",c=!0}b=ue(a);if(!(!c&&a.lineNumber&&a.fileName&&a.stack&&a.message&&a.name)){c=a.message;if(null==
c){if(a.constructor&&a.constructor instanceof Function){if(a.constructor.name)c=a.constructor.name;else if(c=a.constructor,ve[c])c=ve[c];else{c=String(c);if(!ve[c]){var f=/function\s+([^\(]+)/m.exec(c);ve[c]=f?f[1]:"[Anonymous]"}c=ve[c]}c='Unknown Error of type "'+c+'"'}else c="Unknown Error of unknown type";"function"===typeof a.toString&&Object.prototype.toString!==a.toString&&(c+=": "+a.toString())}return{message:c,name:a.name||"UnknownError",lineNumber:d,fileName:e,stack:b||"Not available"}}a.stack=
b;return{message:a.message,name:a.name,lineNumber:a.lineNumber,fileName:a.fileName,stack:a.stack}}
function ue(a,b){b||(b={});b[we(a)]=!0;var c=a.stack||"";(a=a.Pb)&&!b[we(a)]&&(c+="\nCaused by: ",a.stack&&0==a.stack.indexOf(a.toString())||(c+="string"===typeof a?a:a.message+"\n"),c+=ue(a,b));return c}
function we(a){var b="";"function"===typeof a.toString&&(b=""+a);return b+a.stack}
var ve={};var xe=function(){if(!x.addEventListener||!Object.defineProperty)return!1;var a=!1,b=Object.defineProperty({},"passive",{get:function(){a=!0}});
try{x.addEventListener("test",Ma,b),x.removeEventListener("test",Ma,b)}catch(c){}return a}();function ye(a,b){se.call(this,a?a.type:"");this.relatedTarget=this.h=this.target=null;this.button=this.screenY=this.screenX=this.clientY=this.clientX=0;this.key="";this.charCode=this.keyCode=0;this.metaKey=this.shiftKey=this.altKey=this.ctrlKey=!1;this.state=null;this.pointerId=0;this.pointerType="";this.i=null;a&&this.init(a,b)}
$a(ye,se);var ze={2:"touch",3:"pen",4:"mouse"};
ye.prototype.init=function(a,b){var c=this.type=a.type,d=a.changedTouches&&a.changedTouches.length?a.changedTouches[0]:null;this.target=a.target||a.srcElement;this.h=b;if(b=a.relatedTarget){if(vc){a:{try{rc(b.nodeName);var e=!0;break a}catch(f){}e=!1}e||(b=null)}}else"mouseover"==c?b=a.fromElement:"mouseout"==c&&(b=a.toElement);this.relatedTarget=b;d?(this.clientX=void 0!==d.clientX?d.clientX:d.pageX,this.clientY=void 0!==d.clientY?d.clientY:d.pageY,this.screenX=d.screenX||0,this.screenY=d.screenY||
0):(this.clientX=void 0!==a.clientX?a.clientX:a.pageX,this.clientY=void 0!==a.clientY?a.clientY:a.pageY,this.screenX=a.screenX||0,this.screenY=a.screenY||0);this.button=a.button;this.keyCode=a.keyCode||0;this.key=a.key||"";this.charCode=a.charCode||("keypress"==c?a.keyCode:0);this.ctrlKey=a.ctrlKey;this.altKey=a.altKey;this.shiftKey=a.shiftKey;this.metaKey=a.metaKey;this.pointerId=a.pointerId||0;this.pointerType="string"===typeof a.pointerType?a.pointerType:ze[a.pointerType]||"";this.state=a.state;
this.i=a;a.defaultPrevented&&ye.aa.preventDefault.call(this)};
ye.prototype.stopPropagation=function(){ye.aa.stopPropagation.call(this);this.i.stopPropagation?this.i.stopPropagation():this.i.cancelBubble=!0};
ye.prototype.preventDefault=function(){ye.aa.preventDefault.call(this);var a=this.i;a.preventDefault?a.preventDefault():a.returnValue=!1};var Ae="closure_listenable_"+(1E6*Math.random()|0);var Be=0;function Ce(a,b,c,d,e){this.listener=a;this.proxy=null;this.src=b;this.type=c;this.capture=!!d;this.La=e;this.key=++Be;this.ya=this.Ha=!1}
function De(a){a.ya=!0;a.listener=null;a.proxy=null;a.src=null;a.La=null}
;function Ee(a){this.src=a;this.listeners={};this.h=0}
Ee.prototype.add=function(a,b,c,d,e){var f=a.toString();a=this.listeners[f];a||(a=this.listeners[f]=[],this.h++);var g=Fe(a,b,d,e);-1<g?(b=a[g],c||(b.Ha=!1)):(b=new Ce(b,this.src,f,!!d,e),b.Ha=c,a.push(b));return b};
Ee.prototype.remove=function(a,b,c,d){a=a.toString();if(!(a in this.listeners))return!1;var e=this.listeners[a];b=Fe(e,b,c,d);return-1<b?(De(e[b]),Array.prototype.splice.call(e,b,1),0==e.length&&(delete this.listeners[a],this.h--),!0):!1};
function Ge(a,b){var c=b.type;c in a.listeners&&lb(a.listeners[c],b)&&(De(b),0==a.listeners[c].length&&(delete a.listeners[c],a.h--))}
function Fe(a,b,c,d){for(var e=0;e<a.length;++e){var f=a[e];if(!f.ya&&f.listener==b&&f.capture==!!c&&f.La==d)return e}return-1}
;var He="closure_lm_"+(1E6*Math.random()|0),Ie={},Je=0;function Ke(a,b,c,d,e){if(d&&d.once)Le(a,b,c,d,e);else if(Array.isArray(b))for(var f=0;f<b.length;f++)Ke(a,b[f],c,d,e);else c=Me(c),a&&a[Ae]?a.W(b,c,Ra(d)?!!d.capture:!!d,e):Ne(a,b,c,!1,d,e)}
function Ne(a,b,c,d,e,f){if(!b)throw Error("Invalid event type");var g=Ra(e)?!!e.capture:!!e,h=Oe(a);h||(a[He]=h=new Ee(a));c=h.add(b,c,d,g,f);if(!c.proxy){d=Pe();c.proxy=d;d.src=a;d.listener=c;if(a.addEventListener)xe||(e=g),void 0===e&&(e=!1),a.addEventListener(b.toString(),d,e);else if(a.attachEvent)a.attachEvent(Qe(b.toString()),d);else if(a.addListener&&a.removeListener)a.addListener(d);else throw Error("addEventListener and attachEvent are unavailable.");Je++}}
function Pe(){function a(c){return b.call(a.src,a.listener,c)}
var b=Re;return a}
function Le(a,b,c,d,e){if(Array.isArray(b))for(var f=0;f<b.length;f++)Le(a,b[f],c,d,e);else c=Me(c),a&&a[Ae]?a.l.add(String(b),c,!0,Ra(d)?!!d.capture:!!d,e):Ne(a,b,c,!0,d,e)}
function Se(a,b,c,d,e){if(Array.isArray(b))for(var f=0;f<b.length;f++)Se(a,b[f],c,d,e);else(d=Ra(d)?!!d.capture:!!d,c=Me(c),a&&a[Ae])?a.l.remove(String(b),c,d,e):a&&(a=Oe(a))&&(b=a.listeners[b.toString()],a=-1,b&&(a=Fe(b,c,d,e)),(c=-1<a?b[a]:null)&&Te(c))}
function Te(a){if("number"!==typeof a&&a&&!a.ya){var b=a.src;if(b&&b[Ae])Ge(b.l,a);else{var c=a.type,d=a.proxy;b.removeEventListener?b.removeEventListener(c,d,a.capture):b.detachEvent?b.detachEvent(Qe(c),d):b.addListener&&b.removeListener&&b.removeListener(d);Je--;(c=Oe(b))?(Ge(c,a),0==c.h&&(c.src=null,b[He]=null)):De(a)}}}
function Qe(a){return a in Ie?Ie[a]:Ie[a]="on"+a}
function Re(a,b){if(a.ya)a=!0;else{b=new ye(b,this);var c=a.listener,d=a.La||a.src;a.Ha&&Te(a);a=c.call(d,b)}return a}
function Oe(a){a=a[He];return a instanceof Ee?a:null}
var Ue="__closure_events_fn_"+(1E9*Math.random()>>>0);function Me(a){if("function"===typeof a)return a;a[Ue]||(a[Ue]=function(b){return a.handleEvent(b)});
return a[Ue]}
;function Ve(){K.call(this);this.l=new Ee(this);this.Y=this;this.L=null}
$a(Ve,K);Ve.prototype[Ae]=!0;Ve.prototype.addEventListener=function(a,b,c,d){Ke(this,a,b,c,d)};
Ve.prototype.removeEventListener=function(a,b,c,d){Se(this,a,b,c,d)};
function We(a,b){var c=a.L;if(c){var d=[];for(var e=1;c;c=c.L)d.push(c),++e}a=a.Y;c=b.type||b;"string"===typeof b?b=new se(b,a):b instanceof se?b.target=b.target||a:(e=b,b=new se(c,a),zb(b,e));e=!0;if(d)for(var f=d.length-1;!b.j&&0<=f;f--){var g=b.h=d[f];e=Xe(g,c,!0,b)&&e}b.j||(g=b.h=a,e=Xe(g,c,!0,b)&&e,b.j||(e=Xe(g,c,!1,b)&&e));if(d)for(f=0;!b.j&&f<d.length;f++)g=b.h=d[f],e=Xe(g,c,!1,b)&&e}
Ve.prototype.I=function(){Ve.aa.I.call(this);if(this.l){var a=this.l,b=0,c;for(c in a.listeners){for(var d=a.listeners[c],e=0;e<d.length;e++)++b,De(d[e]);delete a.listeners[c];a.h--}}this.L=null};
Ve.prototype.W=function(a,b,c,d){return this.l.add(String(a),b,!1,c,d)};
function Xe(a,b,c,d){b=a.l.listeners[String(b)];if(!b)return!0;b=b.concat();for(var e=!0,f=0;f<b.length;++f){var g=b[f];if(g&&!g.ya&&g.capture==c){var h=g.listener,k=g.La||g.src;g.Ha&&Ge(a.l,g);e=!1!==h.call(k,d)&&e}}return e&&!d.defaultPrevented}
;function Ye(a){Ve.call(this);var b=this;this.A=this.j=0;this.V=null!=a?a:{N:function(e,f){return setTimeout(e,f)},
U:clearTimeout};var c,d;this.i=null!=(d=null==(c=window.navigator)?void 0:c.onLine)?d:!0;this.m=function(){return w(function(e){return t(e,Ze(b),0)})};
window.addEventListener("offline",this.m);window.addEventListener("online",this.m);this.A||$e(this)}
r(Ye,Ve);function af(){var a=bf;Ye.h||(Ye.h=new Ye(a));return Ye.h}
Ye.prototype.dispose=function(){window.removeEventListener("offline",this.m);window.removeEventListener("online",this.m);this.V.U(this.A);delete Ye.h};
Ye.prototype.H=function(){return this.i};
function $e(a){a.A=a.V.N(function(){var b;return w(function(c){if(1==c.h)return a.i?(null==(b=window.navigator)?0:b.onLine)?c.s(3):t(c,Ze(a),3):t(c,Ze(a),3);$e(a);c.h=0})},3E4)}
function Ze(a,b){return a.u?a.u:a.u=new Promise(function(c){var d,e,f,g;return w(function(h){switch(h.h){case 1:return d=window.AbortController?new window.AbortController:void 0,f=null==(e=d)?void 0:e.signal,g=!1,wa(h,2,3),d&&(a.j=a.V.N(function(){d.abort()},b||2E4)),t(h,fetch("/generate_204",{method:"HEAD",
signal:f}),5);case 5:g=!0;case 3:za(h);a.u=void 0;a.j&&(a.V.U(a.j),a.j=0);g!==a.i&&(a.i=g,a.i?We(a,"networkstatus-online"):We(a,"networkstatus-offline"));c(g);Aa(h);break;case 2:ya(h),g=!1,h.s(3)}})})}
;var cf={xo:"WEB_DISPLAY_MODE_UNKNOWN",to:"WEB_DISPLAY_MODE_BROWSER",vo:"WEB_DISPLAY_MODE_MINIMAL_UI",wo:"WEB_DISPLAY_MODE_STANDALONE",uo:"WEB_DISPLAY_MODE_FULLSCREEN"};function df(){this.data_=[];this.h=-1}
df.prototype.set=function(a,b){b=void 0===b?!0:b;0<=a&&52>a&&0===a%1&&this.data_[a]!=b&&(this.data_[a]=b,this.h=-1)};
df.prototype.get=function(a){return!!this.data_[a]};
function ef(a){-1==a.h&&(a.h=jb(a.data_,function(b,c,d){return c?b+Math.pow(2,d):b},0));
return a.h}
;function ff(a,b){this.j=a;this.l=b;this.i=0;this.h=null}
ff.prototype.get=function(){if(0<this.i){this.i--;var a=this.h;this.h=a.next;a.next=null}else a=this.j();return a};
function gf(a,b){a.l(b);100>a.i&&(a.i++,b.next=a.h,a.h=b)}
;var hf;function jf(){var a=x.MessageChannel;"undefined"===typeof a&&"undefined"!==typeof window&&window.postMessage&&window.addEventListener&&!B("Presto")&&(a=function(){var e=Md("IFRAME");e.style.display="none";document.documentElement.appendChild(e);var f=e.contentWindow;e=f.document;e.open();e.close();var g="callImmediate"+Math.random(),h="file:"==f.location.protocol?"*":f.location.protocol+"//"+f.location.host;e=Xa(function(k){if(("*"==h||k.origin==h)&&k.data==g)this.port1.onmessage()},this);
f.addEventListener("message",e,!1);this.port1={};this.port2={postMessage:function(){f.postMessage(g,h)}}});
if("undefined"!==typeof a&&!B("Trident")&&!B("MSIE")){var b=new a,c={},d=c;b.port1.onmessage=function(){if(void 0!==c.next){c=c.next;var e=c.nb;c.nb=null;e()}};
return function(e){d.next={nb:e};d=d.next;b.port2.postMessage(0)}}return function(e){x.setTimeout(e,0)}}
;function kf(a){x.setTimeout(function(){throw a;},0)}
;function lf(){this.i=this.h=null}
lf.prototype.add=function(a,b){var c=mf.get();c.set(a,b);this.i?this.i.next=c:this.h=c;this.i=c};
lf.prototype.remove=function(){var a=null;this.h&&(a=this.h,this.h=this.h.next,this.h||(this.i=null),a.next=null);return a};
var mf=new ff(function(){return new nf},function(a){return a.reset()});
function nf(){this.next=this.scope=this.h=null}
nf.prototype.set=function(a,b){this.h=a;this.scope=b;this.next=null};
nf.prototype.reset=function(){this.next=this.scope=this.h=null};function of(a,b){pf||qf();rf||(pf(),rf=!0);sf.add(a,b)}
var pf;function qf(){if(x.Promise&&x.Promise.resolve){var a=x.Promise.resolve(void 0);pf=function(){a.then(tf)}}else pf=function(){var b=tf;
"function"!==typeof x.setImmediate||x.Window&&x.Window.prototype&&!B("Edge")&&x.Window.prototype.setImmediate==x.setImmediate?(hf||(hf=jf()),hf(b)):x.setImmediate(b)}}
var rf=!1,sf=new lf;function tf(){for(var a;a=sf.remove();){try{a.h.call(a.scope)}catch(b){kf(b)}gf(mf,a)}rf=!1}
;function uf(a,b){this.h=a[x.Symbol.iterator]();this.i=b}
uf.prototype[Symbol.iterator]=function(){return this};
uf.prototype.next=function(){var a=this.h.next();return{value:a.done?void 0:this.i.call(void 0,a.value),done:a.done}};
function vf(a,b){return new uf(a,b)}
;function wf(){this.blockSize=-1}
;function xf(){this.blockSize=-1;this.blockSize=64;this.h=[];this.o=[];this.m=[];this.j=[];this.j[0]=128;for(var a=1;a<this.blockSize;++a)this.j[a]=0;this.l=this.i=0;this.reset()}
$a(xf,wf);xf.prototype.reset=function(){this.h[0]=1732584193;this.h[1]=4023233417;this.h[2]=2562383102;this.h[3]=271733878;this.h[4]=3285377520;this.l=this.i=0};
function yf(a,b,c){c||(c=0);var d=a.m;if("string"===typeof b)for(var e=0;16>e;e++)d[e]=b.charCodeAt(c)<<24|b.charCodeAt(c+1)<<16|b.charCodeAt(c+2)<<8|b.charCodeAt(c+3),c+=4;else for(e=0;16>e;e++)d[e]=b[c]<<24|b[c+1]<<16|b[c+2]<<8|b[c+3],c+=4;for(e=16;80>e;e++){var f=d[e-3]^d[e-8]^d[e-14]^d[e-16];d[e]=(f<<1|f>>>31)&4294967295}b=a.h[0];c=a.h[1];var g=a.h[2],h=a.h[3],k=a.h[4];for(e=0;80>e;e++){if(40>e)if(20>e){f=h^c&(g^h);var m=1518500249}else f=c^g^h,m=1859775393;else 60>e?(f=c&g|h&(c|g),m=2400959708):
(f=c^g^h,m=3395469782);f=(b<<5|b>>>27)+f+k+m+d[e]&4294967295;k=h;h=g;g=(c<<30|c>>>2)&4294967295;c=b;b=f}a.h[0]=a.h[0]+b&4294967295;a.h[1]=a.h[1]+c&4294967295;a.h[2]=a.h[2]+g&4294967295;a.h[3]=a.h[3]+h&4294967295;a.h[4]=a.h[4]+k&4294967295}
xf.prototype.update=function(a,b){if(null!=a){void 0===b&&(b=a.length);for(var c=b-this.blockSize,d=0,e=this.o,f=this.i;d<b;){if(0==f)for(;d<=c;)yf(this,a,d),d+=this.blockSize;if("string"===typeof a)for(;d<b;){if(e[f]=a.charCodeAt(d),++f,++d,f==this.blockSize){yf(this,e);f=0;break}}else for(;d<b;)if(e[f]=a[d],++f,++d,f==this.blockSize){yf(this,e);f=0;break}}this.i=f;this.l+=b}};
xf.prototype.digest=function(){var a=[],b=8*this.l;56>this.i?this.update(this.j,56-this.i):this.update(this.j,this.blockSize-(this.i-56));for(var c=this.blockSize-1;56<=c;c--)this.o[c]=b&255,b/=256;yf(this,this.o);for(c=b=0;5>c;c++)for(var d=24;0<=d;d-=8)a[b]=this.h[c]>>d&255,++b;return a};function zf(a){return"string"==typeof a.className?a.className:a.getAttribute&&a.getAttribute("class")||""}
function Af(a,b){"string"==typeof a.className?a.className=b:a.setAttribute&&a.setAttribute("class",b)}
function Bf(a,b){a.classList?b=a.classList.contains(b):(a=a.classList?a.classList:zf(a).match(/\S+/g)||[],b=0<=fb(a,b));return b}
function Cf(){var a=document.body;a.classList?a.classList.remove("inverted-hdpi"):Bf(a,"inverted-hdpi")&&Af(a,Array.prototype.filter.call(a.classList?a.classList:zf(a).match(/\S+/g)||[],function(b){return"inverted-hdpi"!=b}).join(" "))}
;function Df(){}
Df.prototype.next=function(){return Ef};
var Ef={done:!0,value:void 0};function Ff(a){return{value:a,done:!1}}
Df.prototype.Z=function(){return this};function Gf(a){if(a instanceof Hf||a instanceof If||a instanceof Jf)return a;if("function"==typeof a.next)return new Hf(function(){return a});
if("function"==typeof a[Symbol.iterator])return new Hf(function(){return a[Symbol.iterator]()});
if("function"==typeof a.Z)return new Hf(function(){return a.Z()});
throw Error("Not an iterator or iterable.");}
function Hf(a){this.i=a}
Hf.prototype.Z=function(){return new If(this.i())};
Hf.prototype[Symbol.iterator]=function(){return new Jf(this.i())};
Hf.prototype.h=function(){return new Jf(this.i())};
function If(a){this.i=a}
r(If,Df);If.prototype.next=function(){return this.i.next()};
If.prototype[Symbol.iterator]=function(){return new Jf(this.i)};
If.prototype.h=function(){return new Jf(this.i)};
function Jf(a){Hf.call(this,function(){return a});
this.j=a}
r(Jf,Hf);Jf.prototype.next=function(){return this.j.next()};function Kf(a,b){this.i={};this.h=[];this.ia=this.size=0;var c=arguments.length;if(1<c){if(c%2)throw Error("Uneven number of arguments");for(var d=0;d<c;d+=2)this.set(arguments[d],arguments[d+1])}else if(a)if(a instanceof Kf)for(c=a.Ya(),d=0;d<c.length;d++)this.set(c[d],a.get(c[d]));else for(d in a)this.set(d,a[d])}
l=Kf.prototype;l.Ya=function(){Lf(this);return this.h.concat()};
l.has=function(a){return Mf(this.i,a)};
l.equals=function(a,b){if(this===a)return!0;if(this.size!=a.size)return!1;b=b||Nf;Lf(this);for(var c,d=0;c=this.h[d];d++)if(!b(this.get(c),a.get(c)))return!1;return!0};
function Nf(a,b){return a===b}
l.isEmpty=function(){return 0==this.size};
l.clear=function(){this.i={};this.ia=this.size=this.h.length=0};
l.remove=function(a){return this.delete(a)};
l.delete=function(a){return Mf(this.i,a)?(delete this.i[a],--this.size,this.ia++,this.h.length>2*this.size&&Lf(this),!0):!1};
function Lf(a){if(a.size!=a.h.length){for(var b=0,c=0;b<a.h.length;){var d=a.h[b];Mf(a.i,d)&&(a.h[c++]=d);b++}a.h.length=c}if(a.size!=a.h.length){var e={};for(c=b=0;b<a.h.length;)d=a.h[b],Mf(e,d)||(a.h[c++]=d,e[d]=1),b++;a.h.length=c}}
l.get=function(a,b){return Mf(this.i,a)?this.i[a]:b};
l.set=function(a,b){Mf(this.i,a)||(this.size+=1,this.h.push(a),this.ia++);this.i[a]=b};
l.forEach=function(a,b){for(var c=this.Ya(),d=0;d<c.length;d++){var e=c[d],f=this.get(e);a.call(b,f,e,this)}};
l.clone=function(){return new Kf(this)};
l.keys=function(){return Gf(this.Z(!0)).h()};
l.values=function(){return Gf(this.Z(!1)).h()};
l.entries=function(){var a=this;return vf(this.keys(),function(b){return[b,a.get(b)]})};
l.Z=function(a){Lf(this);var b=0,c=this.ia,d=this,e=new Df;e.next=function(){if(c!=d.ia)throw Error("The map has changed since the iterator was created");if(b>=d.h.length)return Ef;var f=d.h[b++];return Ff(a?f:d.i[f])};
return e};
function Mf(a,b){return Object.prototype.hasOwnProperty.call(a,b)}
;function Of(a){Pf();return Kb(a)}
var Pf=Ma;function Sf(a){var b=[];Tf(new Uf,a,b);return b.join("")}
function Uf(){}
function Tf(a,b,c){if(null==b)c.push("null");else{if("object"==typeof b){if(Array.isArray(b)){var d=b;b=d.length;c.push("[");for(var e="",f=0;f<b;f++)c.push(e),Tf(a,d[f],c),e=",";c.push("]");return}if(b instanceof String||b instanceof Number||b instanceof Boolean)b=b.valueOf();else{c.push("{");e="";for(d in b)Object.prototype.hasOwnProperty.call(b,d)&&(f=b[d],"function"!=typeof f&&(c.push(e),Vf(d,c),c.push(":"),Tf(a,f,c),e=","));c.push("}");return}}switch(typeof b){case "string":Vf(b,c);break;case "number":c.push(isFinite(b)&&
!isNaN(b)?String(b):"null");break;case "boolean":c.push(String(b));break;case "function":c.push("null");break;default:throw Error("Unknown type: "+typeof b);}}}
var Wf={'"':'\\"',"\\":"\\\\","/":"\\/","\b":"\\b","\f":"\\f","\n":"\\n","\r":"\\r","\t":"\\t","\v":"\\u000b"},Xf=/\uffff/.test("\uffff")?/[\\"\x00-\x1f\x7f-\uffff]/g:/[\\"\x00-\x1f\x7f-\xff]/g;function Vf(a,b){b.push('"',a.replace(Xf,function(c){var d=Wf[c];d||(d="\\u"+(c.charCodeAt(0)|65536).toString(16).substr(1),Wf[c]=d);return d}),'"')}
;function Yf(a){if(!a)return!1;try{return!!a.$goog_Thenable}catch(b){return!1}}
;function Zf(a){this.h=0;this.C=void 0;this.l=this.i=this.j=null;this.o=this.m=!1;if(a!=Ma)try{var b=this;a.call(void 0,function(c){$f(b,2,c)},function(c){$f(b,3,c)})}catch(c){$f(this,3,c)}}
function ag(){this.next=this.context=this.onRejected=this.i=this.h=null;this.j=!1}
ag.prototype.reset=function(){this.context=this.onRejected=this.i=this.h=null;this.j=!1};
var bg=new ff(function(){return new ag},function(a){a.reset()});
function cg(a,b,c){var d=bg.get();d.i=a;d.onRejected=b;d.context=c;return d}
function dg(a){return new Zf(function(b,c){c(a)})}
Zf.prototype.then=function(a,b,c){return eg(this,"function"===typeof a?a:null,"function"===typeof b?b:null,c)};
Zf.prototype.$goog_Thenable=!0;function fg(a,b){return eg(a,null,b,void 0)}
Zf.prototype.cancel=function(a){if(0==this.h){var b=new gg(a);of(function(){hg(this,b)},this)}};
function hg(a,b){if(0==a.h)if(a.j){var c=a.j;if(c.i){for(var d=0,e=null,f=null,g=c.i;g&&(g.j||(d++,g.h==a&&(e=g),!(e&&1<d)));g=g.next)e||(f=g);e&&(0==c.h&&1==d?hg(c,b):(f?(d=f,d.next==c.l&&(c.l=d),d.next=d.next.next):ig(c),jg(c,e,3,b)))}a.j=null}else $f(a,3,b)}
function kg(a,b){a.i||2!=a.h&&3!=a.h||lg(a);a.l?a.l.next=b:a.i=b;a.l=b}
function eg(a,b,c,d){var e=cg(null,null,null);e.h=new Zf(function(f,g){e.i=b?function(h){try{var k=b.call(d,h);f(k)}catch(m){g(m)}}:f;
e.onRejected=c?function(h){try{var k=c.call(d,h);void 0===k&&h instanceof gg?g(h):f(k)}catch(m){g(m)}}:g});
e.h.j=a;kg(a,e);return e.h}
Zf.prototype.A=function(a){this.h=0;$f(this,2,a)};
Zf.prototype.L=function(a){this.h=0;$f(this,3,a)};
function $f(a,b,c){if(0==a.h){a===c&&(b=3,c=new TypeError("Promise cannot resolve to itself"));a.h=1;a:{var d=c,e=a.A,f=a.L;if(d instanceof Zf){kg(d,cg(e||Ma,f||null,a));var g=!0}else if(Yf(d))d.then(e,f,a),g=!0;else{if(Ra(d))try{var h=d.then;if("function"===typeof h){mg(d,h,e,f,a);g=!0;break a}}catch(k){f.call(a,k);g=!0;break a}g=!1}}g||(a.C=c,a.h=b,a.j=null,lg(a),3!=b||c instanceof gg||ng(a,c))}}
function mg(a,b,c,d,e){function f(k){h||(h=!0,d.call(e,k))}
function g(k){h||(h=!0,c.call(e,k))}
var h=!1;try{b.call(a,g,f)}catch(k){f(k)}}
function lg(a){a.m||(a.m=!0,of(a.u,a))}
function ig(a){var b=null;a.i&&(b=a.i,a.i=b.next,b.next=null);a.i||(a.l=null);return b}
Zf.prototype.u=function(){for(var a;a=ig(this);)jg(this,a,this.h,this.C);this.m=!1};
function jg(a,b,c,d){if(3==c&&b.onRejected&&!b.j)for(;a&&a.o;a=a.j)a.o=!1;if(b.h)b.h.j=null,og(b,c,d);else try{b.j?b.i.call(b.context):og(b,c,d)}catch(e){pg.call(null,e)}gf(bg,b)}
function og(a,b,c){2==b?a.i.call(a.context,c):a.onRejected&&a.onRejected.call(a.context,c)}
function ng(a,b){a.o=!0;of(function(){a.o&&pg.call(null,b)})}
var pg=kf;function gg(a){bb.call(this,a)}
$a(gg,bb);gg.prototype.name="cancel";function L(a){K.call(this);this.u=1;this.l=[];this.m=0;this.i=[];this.j={};this.A=!!a}
$a(L,K);l=L.prototype;l.subscribe=function(a,b,c){var d=this.j[a];d||(d=this.j[a]=[]);var e=this.u;this.i[e]=a;this.i[e+1]=b;this.i[e+2]=c;this.u=e+3;d.push(e);return e};
function qg(a,b,c,d){if(b=a.j[b]){var e=a.i;(b=b.find(function(f){return e[f+1]==c&&e[f+2]==d}))&&a.ta(b)}}
l.ta=function(a){var b=this.i[a];if(b){var c=this.j[b];0!=this.m?(this.l.push(a),this.i[a+1]=Ma):(c&&lb(c,a),delete this.i[a],delete this.i[a+1],delete this.i[a+2])}return!!b};
l.ja=function(a,b){var c=this.j[a];if(c){for(var d=Array(arguments.length-1),e=1,f=arguments.length;e<f;e++)d[e-1]=arguments[e];if(this.A)for(e=0;e<c.length;e++){var g=c[e];rg(this.i[g+1],this.i[g+2],d)}else{this.m++;try{for(e=0,f=c.length;e<f&&!this.h();e++)g=c[e],this.i[g+1].apply(this.i[g+2],d)}finally{if(this.m--,0<this.l.length&&0==this.m)for(;c=this.l.pop();)this.ta(c)}}return 0!=e}return!1};
function rg(a,b,c){of(function(){a.apply(b,c)})}
l.clear=function(a){if(a){var b=this.j[a];b&&(b.forEach(this.ta,this),delete this.j[a])}else this.i.length=0,this.j={}};
l.I=function(){L.aa.I.call(this);this.clear();this.l.length=0};function sg(a){this.h=a}
sg.prototype.set=function(a,b){void 0===b?this.h.remove(a):this.h.set(a,Sf(b))};
sg.prototype.get=function(a){try{var b=this.h.get(a)}catch(c){return}if(null!==b)try{return JSON.parse(b)}catch(c){throw"Storage: Invalid value was encountered";}};
sg.prototype.remove=function(a){this.h.remove(a)};function tg(a){this.h=a}
$a(tg,sg);function ug(a){this.data=a}
function vg(a){return void 0===a||a instanceof ug?a:new ug(a)}
tg.prototype.set=function(a,b){tg.aa.set.call(this,a,vg(b))};
tg.prototype.i=function(a){a=tg.aa.get.call(this,a);if(void 0===a||a instanceof Object)return a;throw"Storage: Invalid value was encountered";};
tg.prototype.get=function(a){if(a=this.i(a)){if(a=a.data,void 0===a)throw"Storage: Invalid value was encountered";}else a=void 0;return a};function wg(a){this.h=a}
$a(wg,tg);wg.prototype.set=function(a,b,c){if(b=vg(b)){if(c){if(c<Date.now()){wg.prototype.remove.call(this,a);return}b.expiration=c}b.creation=Date.now()}wg.aa.set.call(this,a,b)};
wg.prototype.i=function(a){var b=wg.aa.i.call(this,a);if(b){var c=b.creation,d=b.expiration;if(d&&d<Date.now()||c&&c>Date.now())wg.prototype.remove.call(this,a);else return b}};function xg(){}
;function yg(){}
$a(yg,xg);yg.prototype[Symbol.iterator]=function(){return Gf(this.Z(!0)).h()};
yg.prototype.clear=function(){var a=Array.from(this);a=p(a);for(var b=a.next();!b.done;b=a.next())this.remove(b.value)};function zg(a){this.h=a}
$a(zg,yg);l=zg.prototype;l.isAvailable=function(){if(!this.h)return!1;try{return this.h.setItem("__sak","1"),this.h.removeItem("__sak"),!0}catch(a){return!1}};
l.set=function(a,b){try{this.h.setItem(a,b)}catch(c){if(0==this.h.length)throw"Storage mechanism: Storage disabled";throw"Storage mechanism: Quota exceeded";}};
l.get=function(a){a=this.h.getItem(a);if("string"!==typeof a&&null!==a)throw"Storage mechanism: Invalid value was encountered";return a};
l.remove=function(a){this.h.removeItem(a)};
l.Z=function(a){var b=0,c=this.h,d=new Df;d.next=function(){if(b>=c.length)return Ef;var e=c.key(b++);if(a)return Ff(e);e=c.getItem(e);if("string"!==typeof e)throw"Storage mechanism: Invalid value was encountered";return Ff(e)};
return d};
l.clear=function(){this.h.clear()};
l.key=function(a){return this.h.key(a)};function Ag(){var a=null;try{a=window.localStorage||null}catch(b){}this.h=a}
$a(Ag,zg);function Bg(a,b){this.i=a;this.h=null;var c;if(c=tc)c=!(9<=Number(Gc));if(c){Cg||(Cg=new Kf);this.h=Cg.get(a);this.h||(b?this.h=document.getElementById(b):(this.h=document.createElement("userdata"),this.h.addBehavior("#default#userData"),document.body.appendChild(this.h)),Cg.set(a,this.h));try{this.h.load(this.i)}catch(d){this.h=null}}}
$a(Bg,yg);var Dg={".":".2E","!":".21","~":".7E","*":".2A","'":".27","(":".28",")":".29","%":"."},Cg=null;function Eg(a){return"_"+encodeURIComponent(a).replace(/[.!~*'()%]/g,function(b){return Dg[b]})}
l=Bg.prototype;l.isAvailable=function(){return!!this.h};
l.set=function(a,b){this.h.setAttribute(Eg(a),b);Fg(this)};
l.get=function(a){a=this.h.getAttribute(Eg(a));if("string"!==typeof a&&null!==a)throw"Storage mechanism: Invalid value was encountered";return a};
l.remove=function(a){this.h.removeAttribute(Eg(a));Fg(this)};
l.Z=function(a){var b=0,c=this.h.XMLDocument.documentElement.attributes,d=new Df;d.next=function(){if(b>=c.length)return Ef;var e=c[b++];if(a)return Ff(decodeURIComponent(e.nodeName.replace(/\./g,"%")).substr(1));e=e.nodeValue;if("string"!==typeof e)throw"Storage mechanism: Invalid value was encountered";return Ff(e)};
return d};
l.clear=function(){for(var a=this.h.XMLDocument.documentElement,b=a.attributes.length;0<b;b--)a.removeAttribute(a.attributes[b-1].nodeName);Fg(this)};
function Fg(a){try{a.h.save(a.i)}catch(b){throw"Storage mechanism: Quota exceeded";}}
;function Gg(a,b){this.i=a;this.h=b+"::"}
$a(Gg,yg);Gg.prototype.set=function(a,b){this.i.set(this.h+a,b)};
Gg.prototype.get=function(a){return this.i.get(this.h+a)};
Gg.prototype.remove=function(a){this.i.remove(this.h+a)};
Gg.prototype.Z=function(a){var b=this.i[Symbol.iterator](),c=this,d=new Df;d.next=function(){var e=b.next();if(e.done)return e;for(e=e.value;e.substr(0,c.h.length)!=c.h;){e=b.next();if(e.done)return e;e=e.value}return Ff(a?e.substr(c.h.length):c.i.get(e))};
return d};function Hg(a){J.call(this,a)}
r(Hg,J);Hg.prototype.getKey=function(){return id(this,1)};
Hg.prototype.getValue=function(){return id(this,2===ld(this,Ig)?2:-1)};
Hg.prototype.setValue=function(a){return kd(this,2,Ig,a)};
var Ig=[2,3,4,5,6];function Jg(a){J.call(this,a)}
r(Jg,J);function Kg(a){J.call(this,a)}
r(Kg,J);function Lg(a){J.call(this,a)}
r(Lg,J);function Mg(a){J.call(this,a,-1,Ng)}
r(Mg,J);Mg.prototype.getPlayerType=function(){return id(this,36)};
Mg.prototype.setHomeGroupInfo=function(a){return I(this,81,a)};
var Ng=[9,66,24,32,86,100,101];function Og(a){J.call(this,a,-1,Pg)}
r(Og,J);var Pg=[15,26,28];function Qg(a){J.call(this,a)}
r(Qg,J);Qg.prototype.setToken=function(a){return D(this,2,a)};function Rg(a){J.call(this,a,-1,Sg)}
r(Rg,J);Rg.prototype.setSafetyMode=function(a){return D(this,5,a)};
var Sg=[12];function Tg(a){J.call(this,a,-1,Ug)}
r(Tg,J);var Ug=[12];function Vg(a){J.call(this,a,-1,Wg)}
r(Vg,J);function Xg(a){J.call(this,a)}
r(Xg,J);Xg.prototype.getKey=function(){return qd(this,1)};
Xg.prototype.getValue=function(){return qd(this,2)};
Xg.prototype.setValue=function(a){return D(this,2,a)};
var Wg=[4,5];function Yg(a){J.call(this,a)}
r(Yg,J);function Zg(a){J.call(this,a)}
r(Zg,J);var $g=[2,3];function ah(a){J.call(this,a)}
r(ah,J);ah.prototype.getMessage=function(){return qd(this,1)};function bh(a){J.call(this,a)}
r(bh,J);function ch(a){J.call(this,a)}
r(ch,J);function dh(a){J.call(this,a,-1,eh)}
r(dh,J);var eh=[10,17];function fh(a){J.call(this,a)}
r(fh,J);function gh(a){J.call(this,a)}
r(gh,J);gh.prototype.S=function(a){D(this,1,a)};function hh(a){J.call(this,a)}
r(hh,J);function ih(a){J.call(this,a)}
r(ih,J);function jh(a){J.call(this,a)}
r(jh,J);function kh(a,b){I(a,1,b)}
jh.prototype.S=function(a){D(this,2,a)};
function lh(a){J.call(this,a)}
r(lh,J);function mh(a,b){I(a,1,b)}
;function nh(a){J.call(this,a,-1,oh)}
r(nh,J);nh.prototype.S=function(a){D(this,1,a)};
function ph(a,b){I(a,2,b)}
var oh=[3];function qh(a){J.call(this,a)}
r(qh,J);qh.prototype.S=function(a){D(this,1,a)};function rh(a){J.call(this,a)}
r(rh,J);rh.prototype.S=function(a){D(this,1,a)};function sh(a){J.call(this,a)}
r(sh,J);sh.prototype.S=function(a){D(this,1,a)};function th(a){J.call(this,a)}
r(th,J);function uh(a){J.call(this,a)}
r(uh,J);function vh(a){J.call(this,a,-1,wh)}
r(vh,J);vh.prototype.getPlayerType=function(){var a=id(this,7);return null==a?0:a};
vh.prototype.setVideoId=function(a){return D(this,19,a)};
function xh(a,b){pd(a,68,yh,b)}
function yh(a){J.call(this,a)}
r(yh,J);yh.prototype.getId=function(){return qd(this,2)};
var wh=[83,68];function zh(a){J.call(this,a)}
r(zh,J);function Ah(a){J.call(this,a)}
r(Ah,J);function Bh(a){J.call(this,a)}
r(Bh,J);function Ch(a){J.call(this,a,428)}
r(Ch,J);
var Dh=[23,24,11,6,7,5,2,3,20,21,28,32,37,229,241,45,59,225,288,72,73,78,208,156,202,215,74,76,79,80,111,85,91,97,100,102,105,119,126,127,136,146,157,158,159,163,164,168,176,222,383,177,178,179,411,184,188,189,190,191,193,194,195,196,198,199,200,201,203,204,205,206,258,259,260,261,209,226,227,232,233,234,240,247,248,251,254,255,270,278,291,293,300,304,308,309,310,311,313,314,319,321,323,324,328,330,331,332,337,338,340,344,348,350,351,352,353,354,355,356,357,358,361,363,364,368,369,370,373,374,375,
378,380,381,388,389,403,412,413,414,415,416,417,418,419,420,423,424,425,426,427,117];var Eh={Gh:0,rh:1,xh:2,yh:4,Dh:8,zh:16,Ah:32,Fh:64,Eh:128,th:256,vh:512,Ch:1024,uh:2048,wh:4096,sh:8192,Bh:16384};function Fh(a){J.call(this,a)}
r(Fh,J);function Gh(a){J.call(this,a)}
r(Gh,J);Gh.prototype.setVideoId=function(a){return kd(this,1,Hh,a)};
Gh.prototype.getPlaylistId=function(){return id(this,2===ld(this,Hh)?2:-1)};
var Hh=[1,2];function Ih(a){J.call(this,a,-1,Jh)}
r(Ih,J);var Jh=[3];function Kh(a){J.call(this,a,1)}
r(Kh,J);function Lh(a){J.call(this,a)}
r(Lh,J);var Mh;Mh=new function(a,b){this.h=a;this.fieldName=b;this.isRepeated=0;this.i=yd}(406606992,{Ro:0},Lh);function Nh(){Lh.apply(this,arguments)}
r(Nh,Lh);oe(Nh);function Oh(a,b){1<b.length?a[b[0]]=b[1]:1===b.length&&Object.assign(a,b[0])}
;var Ph=x.window,Qh,Rh,Sh=(null==Ph?void 0:null==(Qh=Ph.yt)?void 0:Qh.config_)||(null==Ph?void 0:null==(Rh=Ph.ytcfg)?void 0:Rh.data_)||{},Th,Uh=(null==Ph?void 0:null==(Th=Ph.ytcfg)?void 0:Th.obfuscatedData_)||[];function Vh(){Kh.apply(this,arguments)}
r(Vh,Kh);oe(Vh);var Wh=new Vh(Uh),Xh=Sh.EXPERIMENT_FLAGS;if(!Xh||!Xh.jspb_i18n_extension){var Yh=new Nh;Mh.i(Wh,Yh)}y("yt.config_",Sh,void 0);y("yt.configJspb_",Uh,void 0);function Zh(){Oh(Sh,arguments)}
function A(a,b){return a in Sh?Sh[a]:b}
function $h(a){return A(a,void 0)}
function ai(){var a=Sh.EXPERIMENT_FLAGS;return a?a.web_disable_gel_stp_ecatcher_killswitch:void 0}
;function M(a){a=bi(a);return"string"===typeof a&&"false"===a?!1:!!a}
function ci(a,b){a=bi(a);return void 0===a&&void 0!==b?b:Number(a||0)}
function di(){return A("EXPERIMENTS_TOKEN","")}
function bi(a){var b=A("EXPERIMENTS_FORCED_FLAGS",{});return void 0!==b[a]?b[a]:A("EXPERIMENT_FLAGS",{})[a]}
function ei(){var a=[],b=A("EXPERIMENTS_FORCED_FLAGS",{});for(c in b)a.push({key:c,value:String(b[c])});var c=A("EXPERIMENT_FLAGS",{});for(var d in c)d.startsWith("force_")&&void 0===b[d]&&a.push({key:d,value:String(c[d])});return a}
;var fi=[];function gi(a){fi.forEach(function(b){return b(a)})}
function hi(a){return a&&window.yterr?function(){try{return a.apply(this,arguments)}catch(b){ii(b)}}:a}
function ii(a,b,c,d){var e=z("yt.logging.errors.log");e?e(a,"ERROR",b,c,d):(e=A("ERRORS",[]),e.push([a,"ERROR",b,c,d]),Zh("ERRORS",e));gi(a)}
function ji(a,b,c,d){var e=z("yt.logging.errors.log");e?e(a,"WARNING",b,c,d):(e=A("ERRORS",[]),e.push([a,"WARNING",b,c,d]),Zh("ERRORS",e))}
;function ki(){var a=li;z("yt.ads.biscotti.getId_")||y("yt.ads.biscotti.getId_",a,void 0)}
function mi(a){y("yt.ads.biscotti.lastId_",a,void 0)}
;var ni=/^[\w.]*$/,oi={q:!0,search_query:!0};function pi(a,b){b=a.split(b);for(var c={},d=0,e=b.length;d<e;d++){var f=b[d].split("=");if(1==f.length&&f[0]||2==f.length)try{var g=qi(f[0]||""),h=qi(f[1]||"");g in c?Array.isArray(c[g])?mb(c[g],h):c[g]=[c[g],h]:c[g]=h}catch(u){var k=u,m=f[0],q=String(pi);k.args=[{key:m,value:f[1],query:a,method:ri==q?"unchanged":q}];oi.hasOwnProperty(m)||ji(k)}}return c}
var ri=String(pi);function si(a){var b=[];nb(a,function(c,d){var e=encodeURIComponent(String(d)),f;Array.isArray(c)?f=c:f=[c];gb(f,function(g){""==g?b.push(e):b.push(e+"="+encodeURIComponent(String(g)))})});
return b.join("&")}
function ti(a){"?"==a.charAt(0)&&(a=a.substr(1));return pi(a,"&")}
function ui(a){return-1!=a.indexOf("?")?(a=(a||"").split("#")[0],a=a.split("?",2),ti(1<a.length?a[1]:a[0])):{}}
function vi(a,b,c){var d=a.split("#",2);a=d[0];d=1<d.length?"#"+d[1]:"";var e=a.split("?",2);a=e[0];e=ti(e[1]||"");for(var f in b)!c&&null!==e&&f in e||(e[f]=b[f]);return ic(a,e)+d}
function wi(a){if(!b)var b=window.location.href;var c=dc(1,a),d=ec(a);c&&d?(a=a.match(bc),b=b.match(bc),a=a[3]==b[3]&&a[1]==b[1]&&a[4]==b[4]):a=d?ec(b)==d&&(Number(dc(4,b))||null)==(Number(dc(4,a))||null):!0;return a}
function qi(a){return a&&a.match(ni)?a:decodeURIComponent(a.replace(/\+/g," "))}
;function xi(a){var b=yi;a=void 0===a?z("yt.ads.biscotti.lastId_")||"":a;var c=Object,d=c.assign,e={};e.dt=Yd;e.flash="0";a:{try{var f=b.h.top.location.href}catch(ta){f=2;break a}f=f?f===b.i.location.href?0:1:2}e=(e.frm=f,e);try{e.u_tz=-(new Date).getTimezoneOffset();var g=void 0===g?Cd:g;try{var h=g.history.length}catch(ta){h=0}e.u_his=h;var k;e.u_h=null==(k=Cd.screen)?void 0:k.height;var m;e.u_w=null==(m=Cd.screen)?void 0:m.width;var q;e.u_ah=null==(q=Cd.screen)?void 0:q.availHeight;var u;e.u_aw=
null==(u=Cd.screen)?void 0:u.availWidth;var C;e.u_cd=null==(C=Cd.screen)?void 0:C.colorDepth}catch(ta){}h=b.h;try{var v=h.screenX;var E=h.screenY}catch(ta){}try{var F=h.outerWidth;var H=h.outerHeight}catch(ta){}try{var R=h.innerWidth;var O=h.innerHeight}catch(ta){}try{var S=h.screenLeft;var ka=h.screenTop}catch(ta){}try{R=h.innerWidth,O=h.innerHeight}catch(ta){}try{var N=h.screen.availWidth;var Ba=h.screen.availTop}catch(ta){}v=[S,ka,v,E,N,Ba,F,H,R,O];try{var Oa=(b.h.top||window).document,ua="CSS1Compat"==
Oa.compatMode?Oa.documentElement:Oa.body;var G=(new Kd(ua.clientWidth,ua.clientHeight)).round()}catch(ta){G=new Kd(-12245933,-12245933)}Oa=G;G={};var Ca=void 0===Ca?x:Ca;ua=new df;Ca.SVGElement&&Ca.document.createElementNS&&ua.set(0);E=Sd();E["allow-top-navigation-by-user-activation"]&&ua.set(1);E["allow-popups-to-escape-sandbox"]&&ua.set(2);Ca.crypto&&Ca.crypto.subtle&&ua.set(3);Ca.TextDecoder&&Ca.TextEncoder&&ua.set(4);Ca=ef(ua);G.bc=Ca;G.bih=Oa.height;G.biw=Oa.width;G.brdim=v.join();b=b.i;b=(G.vis=
b.prerendering?3:{visible:1,hidden:2,prerender:3,preview:4,unloaded:5}[b.visibilityState||b.webkitVisibilityState||b.mozVisibilityState||""]||0,G.wgl=!!Cd.WebGLRenderingContext,G);c=d.call(c,e,b);c.ca_type="image";a&&(c.bid=a);return c}
var yi=new function(){var a=window.document;this.h=window;this.i=a};
y("yt.ads_.signals_.getAdSignalsString",function(a){return si(xi(a))},void 0);Date.now();var zi="XMLHttpRequest"in x?function(){return new XMLHttpRequest}:null;
function Ai(){if(!zi)return null;var a=zi();return"open"in a?a:null}
function Bi(a){switch(a&&"status"in a?a.status:-1){case 200:case 201:case 202:case 203:case 204:case 205:case 206:case 304:return!0;default:return!1}}
;function Ci(a,b){"function"===typeof a&&(a=hi(a));return window.setTimeout(a,b)}
function Di(a){window.clearTimeout(a)}
;var Zi={Authorization:"AUTHORIZATION","X-Goog-EOM-Visitor-Id":"EOM_VISITOR_DATA","X-Goog-Visitor-Id":"SANDBOXED_VISITOR_ID","X-Youtube-Domain-Admin-State":"DOMAIN_ADMIN_STATE","X-Youtube-Chrome-Connected":"CHROME_CONNECTED_HEADER","X-YouTube-Client-Name":"INNERTUBE_CONTEXT_CLIENT_NAME","X-YouTube-Client-Version":"INNERTUBE_CONTEXT_CLIENT_VERSION","X-YouTube-Delegation-Context":"INNERTUBE_CONTEXT_SERIALIZED_DELEGATION_CONTEXT","X-YouTube-Device":"DEVICE","X-Youtube-Identity-Token":"ID_TOKEN","X-YouTube-Page-CL":"PAGE_CL",
"X-YouTube-Page-Label":"PAGE_BUILD_LABEL","X-YouTube-Variants-Checksum":"VARIANTS_CHECKSUM"},$i="app debugcss debugjs expflag force_ad_params force_ad_encrypted force_viral_ad_response_params forced_experiments innertube_snapshots innertube_goldens internalcountrycode internalipoverride absolute_experiments conditional_experiments sbb sr_bns_address".split(" ").concat(fa("client_dev_mss_url client_dev_regex_map client_dev_root_url client_rollout_override expflag jsfeat jsmode mods".split(" "))),aj=
!1;
function bj(a,b){b=void 0===b?{}:b;var c=wi(a),d=M("web_ajax_ignore_global_headers_if_set"),e;for(e in Zi){var f=A(Zi[e]);!f||!c&&ec(a)||d&&void 0!==b[e]||!M("enable_web_eom_visitor_data")&&"X-Goog-EOM-Visitor-Id"===e||(b[e]=f)}"X-Goog-EOM-Visitor-Id"in b&&"X-Goog-Visitor-Id"in b&&delete b["X-Goog-Visitor-Id"];if(c||!ec(a))b["X-YouTube-Utc-Offset"]=String(-(new Date).getTimezoneOffset());if(c||!ec(a)){try{var g=(new Intl.DateTimeFormat).resolvedOptions().timeZone}catch(h){}g&&(b["X-YouTube-Time-Zone"]=g)}if(c||
!ec(a))b["X-YouTube-Ad-Signals"]=si(xi(void 0));return b}
function cj(a){var b=window.location.search,c=ec(a);M("debug_handle_relative_url_for_query_forward_killswitch")||c||!wi(a)||(c=document.location.hostname);var d=cc(dc(5,a));d=(c=c&&(c.endsWith("youtube.com")||c.endsWith("youtube-nocookie.com")))&&d&&d.startsWith("/api/");if(!c||d)return a;var e=ti(b),f={};gb($i,function(g){e[g]&&(f[g]=e[g])});
return vi(a,f||{},!1)}
function dj(a,b){var c=b.format||"JSON";a=ej(a,b);var d=fj(a,b),e=!1,f=gj(a,function(k){if(!e){e=!0;h&&Di(h);var m=Bi(k),q=null,u=400<=k.status&&500>k.status,C=500<=k.status&&600>k.status;if(m||u||C)q=hj(a,c,k,b.convertToSafeHtml);if(m)a:if(k&&204==k.status)m=!0;else{switch(c){case "XML":m=0==parseInt(q&&q.return_code,10);break a;case "RAW":m=!0;break a}m=!!q}q=q||{};u=b.context||x;m?b.onSuccess&&b.onSuccess.call(u,k,q):b.onError&&b.onError.call(u,k,q);b.onFinish&&b.onFinish.call(u,k,q)}},b.method,
d,b.headers,b.responseType,b.withCredentials);
if(b.onTimeout&&0<b.timeout){var g=b.onTimeout;var h=Ci(function(){e||(e=!0,f.abort(),Di(h),g.call(b.context||x,f))},b.timeout)}return f}
function ej(a,b){b.includeDomain&&(a=document.location.protocol+"//"+document.location.hostname+(document.location.port?":"+document.location.port:"")+a);var c=A("XSRF_FIELD_NAME",void 0);if(b=b.urlParams)b[c]&&delete b[c],a=vi(a,b||{},!0);return a}
function fj(a,b){var c=A("XSRF_FIELD_NAME",void 0),d=A("XSRF_TOKEN",void 0),e=b.postBody||"",f=b.postParams,g=$h("XSRF_FIELD_NAME"),h;b.headers&&(h=b.headers["Content-Type"]);b.excludeXsrf||ec(a)&&!b.withCredentials&&ec(a)!=document.location.hostname||"POST"!=b.method||h&&"application/x-www-form-urlencoded"!=h||b.postParams&&b.postParams[g]||(f||(f={}),f[c]=d);f&&"string"===typeof e&&(e=ti(e),zb(e,f),e=b.postBodyFormat&&"JSON"==b.postBodyFormat?JSON.stringify(e):hc(e));f=e||f&&!qb(f);!aj&&f&&"POST"!=
b.method&&(aj=!0,ii(Error("AJAX request with postData should use POST")));return e}
function hj(a,b,c,d){var e=null;switch(b){case "JSON":try{var f=c.responseText}catch(g){throw d=Error("Error reading responseText"),d.params=a,ji(d),g;}a=c.getResponseHeader("Content-Type")||"";f&&0<=a.indexOf("json")&&(")]}'\n"===f.substring(0,5)&&(f=f.substring(5)),e=JSON.parse(f));break;case "XML":if(a=(a=c.responseXML)?ij(a):null)e={},gb(a.getElementsByTagName("*"),function(g){e[g.tagName]=jj(g)})}d&&kj(e);
return e}
function kj(a){if(Ra(a))for(var b in a){var c;(c="html_content"==b)||(c=b.length-5,c=0<=c&&b.indexOf("_html",c)==c);if(c){c=b;Eb("HTML that is escaped and sanitized server-side and passed through yt.net.ajax");var d=a[b],e=Bb();d=e?e.createHTML(d):d;a[c]=new Vb(d)}else kj(a[b])}}
function ij(a){return a?(a=("responseXML"in a?a.responseXML:a).getElementsByTagName("root"))&&0<a.length?a[0]:null:null}
function jj(a){var b="";gb(a.childNodes,function(c){b+=c.nodeValue});
return b}
function gj(a,b,c,d,e,f,g){function h(){4==(k&&"readyState"in k?k.readyState:0)&&b&&hi(b)(k)}
c=void 0===c?"GET":c;d=void 0===d?"":d;var k=Ai();if(!k)return null;"onloadend"in k?k.addEventListener("loadend",h,!1):k.onreadystatechange=h;M("debug_forward_web_query_parameters")&&(a=cj(a));k.open(c,a,!0);f&&(k.responseType=f);g&&(k.withCredentials=!0);c="POST"==c&&(void 0===window.FormData||!(d instanceof FormData));if(e=bj(a,e))for(var m in e)k.setRequestHeader(m,e[m]),"content-type"==m.toLowerCase()&&(c=!1);c&&k.setRequestHeader("Content-Type","application/x-www-form-urlencoded");k.send(d);
return k}
;function lj(a){var b=this;this.h=void 0;a.addEventListener("beforeinstallprompt",function(c){c.preventDefault();b.h=c})}
function mj(){if(!x.matchMedia)return"WEB_DISPLAY_MODE_UNKNOWN";try{return x.matchMedia("(display-mode: standalone)").matches?"WEB_DISPLAY_MODE_STANDALONE":x.matchMedia("(display-mode: minimal-ui)").matches?"WEB_DISPLAY_MODE_MINIMAL_UI":x.matchMedia("(display-mode: fullscreen)").matches?"WEB_DISPLAY_MODE_FULLSCREEN":x.matchMedia("(display-mode: browser)").matches?"WEB_DISPLAY_MODE_BROWSER":"WEB_DISPLAY_MODE_UNKNOWN"}catch(a){return"WEB_DISPLAY_MODE_UNKNOWN"}}
function nj(){var a=mj();a=Object.keys(cf).indexOf(a);return-1===a?null:a}
;function oj(a,b,c,d,e){je.set(""+a,b,{Oa:c,path:"/",domain:void 0===d?"youtube.com":d,secure:void 0===e?!1:e})}
function pj(a){return je.get(""+a,void 0)}
function qj(){if(!je.isEnabled())return!1;if(!je.isEmpty())return!0;je.set("TESTCOOKIESENABLED","1",{Oa:60});if("1"!==je.get("TESTCOOKIESENABLED"))return!1;je.remove("TESTCOOKIESENABLED");return!0}
;var rj=z("ytglobal.prefsUserPrefsPrefs_")||{};y("ytglobal.prefsUserPrefsPrefs_",rj,void 0);function sj(){this.h=A("ALT_PREF_COOKIE_NAME","PREF");this.i=A("ALT_PREF_COOKIE_DOMAIN","youtube.com");var a=pj(this.h);if(a){a=decodeURIComponent(a).split("&");for(var b=0;b<a.length;b++){var c=a[b].split("="),d=c[0];(c=c[1])&&(rj[d]=c.toString())}}}
sj.prototype.get=function(a,b){tj(a);uj(a);a=void 0!==rj[a]?rj[a].toString():null;return null!=a?a:b?b:""};
sj.prototype.set=function(a,b){tj(a);uj(a);if(null==b)throw Error("ExpectedNotNull");rj[a]=b.toString()};
function vj(a){return!!((wj("f"+(Math.floor(a/31)+1))||0)&1<<a%31)}
sj.prototype.remove=function(a){tj(a);uj(a);delete rj[a]};
sj.prototype.clear=function(){for(var a in rj)delete rj[a]};
function uj(a){if(/^f([1-9][0-9]*)$/.test(a))throw Error("ExpectedRegexMatch: "+a);}
function tj(a){if(!/^\w+$/.test(a))throw Error("ExpectedRegexMismatch: "+a);}
function wj(a){a=void 0!==rj[a]?rj[a].toString():null;return null!=a&&/^[A-Fa-f0-9]+$/.test(a)?parseInt(a,16):null}
Na(sj);var xj={bluetooth:"CONN_DISCO",cellular:"CONN_CELLULAR_UNKNOWN",ethernet:"CONN_WIFI",none:"CONN_NONE",wifi:"CONN_WIFI",wimax:"CONN_CELLULAR_4G",other:"CONN_UNKNOWN",unknown:"CONN_UNKNOWN","slow-2g":"CONN_CELLULAR_2G","2g":"CONN_CELLULAR_2G","3g":"CONN_CELLULAR_3G","4g":"CONN_CELLULAR_4G"},yj={CONN_DEFAULT:0,CONN_UNKNOWN:1,CONN_NONE:2,CONN_WIFI:3,CONN_CELLULAR_2G:4,CONN_CELLULAR_3G:5,CONN_CELLULAR_4G:6,CONN_CELLULAR_UNKNOWN:7,CONN_DISCO:8,CONN_CELLULAR_5G:9,CONN_WIFI_METERED:10,CONN_CELLULAR_5G_SA:11,
CONN_CELLULAR_5G_NSA:12,CONN_INVALID:31},zj={EFFECTIVE_CONNECTION_TYPE_UNKNOWN:0,EFFECTIVE_CONNECTION_TYPE_OFFLINE:1,EFFECTIVE_CONNECTION_TYPE_SLOW_2G:2,EFFECTIVE_CONNECTION_TYPE_2G:3,EFFECTIVE_CONNECTION_TYPE_3G:4,EFFECTIVE_CONNECTION_TYPE_4G:5},Aj={"slow-2g":"EFFECTIVE_CONNECTION_TYPE_SLOW_2G","2g":"EFFECTIVE_CONNECTION_TYPE_2G","3g":"EFFECTIVE_CONNECTION_TYPE_3G","4g":"EFFECTIVE_CONNECTION_TYPE_4G"};function Bj(){var a=x.navigator;return a?a.connection:void 0}
function Cj(){var a=Bj();if(a){var b=xj[a.type||"unknown"]||"CONN_UNKNOWN";a=xj[a.effectiveType||"unknown"]||"CONN_UNKNOWN";"CONN_CELLULAR_UNKNOWN"===b&&"CONN_UNKNOWN"!==a&&(b=a);if("CONN_UNKNOWN"!==b)return b;if("CONN_UNKNOWN"!==a)return a}}
function Dj(){var a=Bj();if(null!=a&&a.effectiveType)return Aj.hasOwnProperty(a.effectiveType)?Aj[a.effectiveType]:"EFFECTIVE_CONNECTION_TYPE_UNKNOWN"}
;function Ej(){return"INNERTUBE_API_KEY"in Sh&&"INNERTUBE_API_VERSION"in Sh}
function Fj(){return{innertubeApiKey:A("INNERTUBE_API_KEY",void 0),innertubeApiVersion:A("INNERTUBE_API_VERSION",void 0),ab:A("INNERTUBE_CONTEXT_CLIENT_CONFIG_INFO"),bb:A("INNERTUBE_CONTEXT_CLIENT_NAME","WEB"),Wb:A("INNERTUBE_CONTEXT_CLIENT_NAME",1),innertubeContextClientVersion:A("INNERTUBE_CONTEXT_CLIENT_VERSION",void 0),xb:A("INNERTUBE_CONTEXT_HL",void 0),wb:A("INNERTUBE_CONTEXT_GL",void 0),Xb:A("INNERTUBE_HOST_OVERRIDE",void 0)||"",Zb:!!A("INNERTUBE_USE_THIRD_PARTY_AUTH",!1),Yb:!!A("INNERTUBE_OMIT_API_KEY_WHEN_AUTH_HEADER_IS_PRESENT",
!1),appInstallData:A("SERIALIZED_CLIENT_CONFIG_DATA",void 0)}}
function Gj(a){var b={client:{hl:a.xb,gl:a.wb,clientName:a.bb,clientVersion:a.innertubeContextClientVersion,configInfo:a.ab}};navigator.userAgent&&(b.client.userAgent=String(navigator.userAgent));var c=x.devicePixelRatio;c&&1!=c&&(b.client.screenDensityFloat=String(c));c=di();""!==c&&(b.client.experimentsToken=c);c=ei();0<c.length&&(b.request={internalExperimentFlags:c});Hj(a,void 0,b);Ij(a,void 0,b);Jj(void 0,b);Kj(a,void 0,b);Lj(void 0,b);A("DELEGATED_SESSION_ID")&&!M("pageid_as_header_web")&&(b.user=
{onBehalfOfUser:A("DELEGATED_SESSION_ID")});a=Object;c=a.assign;for(var d=b.client,e={},f=p(Object.entries(ti(A("DEVICE","")))),g=f.next();!g.done;g=f.next()){var h=p(g.value);g=h.next().value;h=h.next().value;"cbrand"===g?e.deviceMake=h:"cmodel"===g?e.deviceModel=h:"cbr"===g?e.browserName=h:"cbrver"===g?e.browserVersion=h:"cos"===g?e.osName=h:"cosver"===g?e.osVersion=h:"cplatform"===g&&(e.platform=h)}b.client=c.call(a,d,e);return b}
function Mj(a){var b=new Tg,c=new Mg;D(c,1,a.xb);D(c,2,a.wb);D(c,16,a.Wb);D(c,17,a.innertubeContextClientVersion);if(a.ab){var d=a.ab,e=new Jg;d.coldConfigData&&D(e,1,d.coldConfigData);d.appInstallData&&D(e,6,d.appInstallData);d.coldHashData&&D(e,3,d.coldHashData);d.hotHashData&&D(e,5,d.hotHashData);I(c,62,e)}(d=x.devicePixelRatio)&&1!=d&&D(c,65,d);d=di();""!==d&&D(c,54,d);d=ei();if(0<d.length){e=new Og;for(var f=0;f<d.length;f++){var g=new Hg;D(g,1,d[f].key);g.setValue(d[f].value);pd(e,15,Hg,g)}I(b,
5,e)}Hj(a,c);Ij(a,c);Jj(c);Kj(a,c);Lj(c);A("DELEGATED_SESSION_ID")&&!M("pageid_as_header_web")&&(a=new Rg,D(a,3,A("DELEGATED_SESSION_ID")));a=p(Object.entries(ti(A("DEVICE",""))));for(d=a.next();!d.done;d=a.next())e=p(d.value),d=e.next().value,e=e.next().value,"cbrand"===d?D(c,12,e):"cmodel"===d?D(c,13,e):"cbr"===d?D(c,87,e):"cbrver"===d?D(c,88,e):"cos"===d?D(c,18,e):"cosver"===d?D(c,19,e):"cplatform"===d&&D(c,42,e);I(b,1,c);return b}
function Hj(a,b,c){a=a.bb;if("WEB"===a||"MWEB"===a||1===a||2===a)if(b){c=md(b,Kg,96)||new Kg;var d=nj();null!==d&&D(c,3,d);I(b,96,c)}else c&&(c.client.mainAppWebInfo=null!=(d=c.client.mainAppWebInfo)?d:{},c.client.mainAppWebInfo.webDisplayMode=mj())}
function Ij(a,b,c){a=a.bb;if(("WEB_REMIX"===a||76===a)&&!M("music_web_display_mode_killswitch"))if(b){var d;c=null!=(d=md(b,Lg,70))?d:new Lg;d=nj();null!==d&&D(c,10,d);I(b,70,c)}else if(c){var e;c.client.Ab=null!=(e=c.client.Ab)?e:{};c.client.Ab.webDisplayMode=mj()}}
function Jj(a,b){var c;if(M("web_log_memory_total_kbytes")&&(null==(c=x.navigator)?0:c.deviceMemory)){var d;c=null==(d=x.navigator)?void 0:d.deviceMemory;a?D(a,95,1E6*c):b&&(b.client.memoryTotalKbytes=""+1E6*c)}}
function Kj(a,b,c){if(a.appInstallData)if(b){var d;c=null!=(d=md(b,Jg,62))?d:new Jg;D(c,6,a.appInstallData);I(b,62,c)}else c&&(c.client.configInfo=c.client.configInfo||{},c.client.configInfo.appInstallData=a.appInstallData)}
function Lj(a,b){var c=Cj();c&&(a?D(a,61,yj[c]):b&&(b.client.connectionType=c));M("web_log_effective_connection_type")&&(c=Dj())&&(a?D(a,94,zj[c]):b&&(b.client.effectiveConnectionType=c))}
function Nj(a,b,c){c=void 0===c?{}:c;var d={};M("enable_web_eom_visitor_data")&&A("EOM_VISITOR_DATA")?d={"X-Goog-EOM-Visitor-Id":A("EOM_VISITOR_DATA")}:d={"X-Goog-Visitor-Id":c.visitorData||A("VISITOR_DATA","")};if(b&&b.includes("www.youtube-nocookie.com"))return d;(b=c.Mo||A("AUTHORIZATION"))||(a?b="Bearer "+z("gapi.auth.getToken")().Lo:b=ne([]));b&&(d.Authorization=b,d["X-Goog-AuthUser"]=A("SESSION_INDEX",0),M("pageid_as_header_web")&&(d["X-Goog-PageId"]=A("DELEGATED_SESSION_ID")));return d}
;function Oj(a){a=Object.assign({},a);delete a.Authorization;var b=ne();if(b){var c=new xf;c.update(A("INNERTUBE_API_KEY",void 0));c.update(b);a.hash=Mc(c.digest(),3)}return a}
;function Pj(a){var b=new Ag;(b=b.isAvailable()?a?new Gg(b,a):b:null)||(a=new Bg(a||"UserDataSharedStore"),b=a.isAvailable()?a:null);this.h=(a=b)?new wg(a):null;this.i=document.domain||window.location.hostname}
Pj.prototype.set=function(a,b,c,d){c=c||31104E3;this.remove(a);if(this.h)try{this.h.set(a,b,Date.now()+1E3*c);return}catch(f){}var e="";if(d)try{e=escape(Sf(b))}catch(f){return}else e=escape(b);oj(a,e,c,this.i)};
Pj.prototype.get=function(a,b){var c=void 0,d=!this.h;if(!d)try{c=this.h.get(a)}catch(e){d=!0}if(d&&(c=pj(a))&&(c=unescape(c),b))try{c=JSON.parse(c)}catch(e){this.remove(a),c=void 0}return c};
Pj.prototype.remove=function(a){this.h&&this.h.remove(a);var b=this.i;je.remove(""+a,"/",void 0===b?"youtube.com":b)};var Qj=window,P=Qj.ytcsi&&Qj.ytcsi.now?Qj.ytcsi.now:Qj.performance&&Qj.performance.timing&&Qj.performance.now&&Qj.performance.timing.navigationStart?function(){return Qj.performance.timing.navigationStart+Qj.performance.now()}:function(){return(new Date).getTime()};var Rj;function Sj(){Rj||(Rj=new Pj("yt.innertube"));return Rj}
function Tj(a,b,c,d){if(d)return null;d=Sj().get("nextId",!0)||1;var e=Sj().get("requests",!0)||{};e[d]={method:a,request:b,authState:Oj(c),requestTime:Math.round(P())};Sj().set("nextId",d+1,86400,!0);Sj().set("requests",e,86400,!0);return d}
function Uj(a){var b=Sj().get("requests",!0)||{};delete b[a];Sj().set("requests",b,86400,!0)}
function Vj(a){var b=Sj().get("requests",!0);if(b){for(var c in b){var d=b[c];if(!(6E4>Math.round(P())-d.requestTime)){var e=d.authState,f=Oj(Nj(!1));vb(e,f)&&(e=d.request,"requestTimeMs"in e&&(e.requestTimeMs=Math.round(P())),Wj(a,d.method,e,{}));delete b[c]}}Sj().set("requests",b,86400,!0)}}
;function Xj(){}
function Yj(a,b){return Zj(a,0,b)}
Xj.prototype.N=function(a,b){return Zj(a,1,b)};
function ak(a,b){Zj(a,2,b)}
function bk(a){var b=z("yt.scheduler.instance.addImmediateJob");b?b(a):a()}
;function ck(){Xj.apply(this,arguments)}
r(ck,Xj);function dk(){ck.h||(ck.h=new ck);return ck.h}
function Zj(a,b,c){void 0!==c&&Number.isNaN(Number(c))&&(c=void 0);var d=z("yt.scheduler.instance.addJob");return d?d(a,b,c):void 0===c?(a(),NaN):Ci(a,c||0)}
ck.prototype.U=function(a){if(void 0===a||!Number.isNaN(Number(a))){var b=z("yt.scheduler.instance.cancelJob");b?b(a):Di(a)}};
ck.prototype.start=function(){var a=z("yt.scheduler.instance.start");a&&a()};
ck.prototype.pause=function(){var a=z("yt.scheduler.instance.pause");a&&a()};var bf=dk();var ek=Hc||Ic;function fk(a){var b=Sb();return b?0<=b.toLowerCase().indexOf(a):!1}
;var gk=function(){var a;return function(){a||(a=new Pj("ytidb"));return a}}();
function hk(){var a;return null==(a=gk())?void 0:a.get("LAST_RESULT_ENTRY_KEY",!0)}
;var ik=[],jk,kk=!1;function lk(){var a={};for(jk=new mk(void 0===a.handleError?nk:a.handleError,void 0===a.logEvent?ok:a.logEvent);0<ik.length;)switch(a=ik.shift(),a.type){case "ERROR":jk.handleError(a.payload);break;case "EVENT":jk.logEvent(a.eventType,a.payload)}}
function pk(a){kk||(jk?jk.handleError(a):(ik.push({type:"ERROR",payload:a}),10<ik.length&&ik.shift()))}
function qk(a,b){kk||(jk?jk.logEvent(a,b):(ik.push({type:"EVENT",eventType:a,payload:b}),10<ik.length&&ik.shift()))}
;function Q(a){var b=Ja.apply(1,arguments);var c=Error.call(this,a);this.message=c.message;"stack"in c&&(this.stack=c.stack);this.args=[].concat(fa(b))}
r(Q,Error);function rk(){try{return sk(),!0}catch(a){return!1}}
function sk(a){if(void 0!==A("DATASYNC_ID",void 0))return A("DATASYNC_ID",void 0);throw new Q("Datasync ID not set",void 0===a?"unknown":a);}
;function tk(a){if(0<=a.indexOf(":"))throw Error("Database name cannot contain ':'");}
function uk(a){return a.substr(0,a.indexOf(":"))||a}
;var vk={},wk=(vk.AUTH_INVALID="No user identifier specified.",vk.EXPLICIT_ABORT="Transaction was explicitly aborted.",vk.IDB_NOT_SUPPORTED="IndexedDB is not supported.",vk.MISSING_INDEX="Index not created.",vk.MISSING_OBJECT_STORES="Object stores not created.",vk.DB_DELETED_BY_MISSING_OBJECT_STORES="Database is deleted because expected object stores were not created.",vk.DB_REOPENED_BY_MISSING_OBJECT_STORES="Database is reopened because expected object stores were not created.",vk.UNKNOWN_ABORT="Transaction was aborted for unknown reasons.",
vk.QUOTA_EXCEEDED="The current transaction exceeded its quota limitations.",vk.QUOTA_MAYBE_EXCEEDED="The current transaction may have failed because of exceeding quota limitations.",vk.EXECUTE_TRANSACTION_ON_CLOSED_DB="Can't start a transaction on a closed database",vk.INCOMPATIBLE_DB_VERSION="The binary is incompatible with the database version",vk),xk={},yk=(xk.AUTH_INVALID="ERROR",xk.EXECUTE_TRANSACTION_ON_CLOSED_DB="WARNING",xk.EXPLICIT_ABORT="IGNORED",xk.IDB_NOT_SUPPORTED="ERROR",xk.MISSING_INDEX=
"WARNING",xk.MISSING_OBJECT_STORES="ERROR",xk.DB_DELETED_BY_MISSING_OBJECT_STORES="WARNING",xk.DB_REOPENED_BY_MISSING_OBJECT_STORES="WARNING",xk.QUOTA_EXCEEDED="WARNING",xk.QUOTA_MAYBE_EXCEEDED="WARNING",xk.UNKNOWN_ABORT="WARNING",xk.INCOMPATIBLE_DB_VERSION="WARNING",xk),zk={},Ak=(zk.AUTH_INVALID=!1,zk.EXECUTE_TRANSACTION_ON_CLOSED_DB=!1,zk.EXPLICIT_ABORT=!1,zk.IDB_NOT_SUPPORTED=!1,zk.MISSING_INDEX=!1,zk.MISSING_OBJECT_STORES=!1,zk.DB_DELETED_BY_MISSING_OBJECT_STORES=!1,zk.DB_REOPENED_BY_MISSING_OBJECT_STORES=
!1,zk.QUOTA_EXCEEDED=!1,zk.QUOTA_MAYBE_EXCEEDED=!0,zk.UNKNOWN_ABORT=!0,zk.INCOMPATIBLE_DB_VERSION=!1,zk);function Bk(a,b,c,d,e){b=void 0===b?{}:b;c=void 0===c?wk[a]:c;d=void 0===d?yk[a]:d;e=void 0===e?Ak[a]:e;Q.call(this,c,Object.assign({},{name:"YtIdbKnownError",isSw:void 0===self.document,isIframe:self!==self.top,type:a},b));this.type=a;this.message=c;this.level=d;this.h=e;Object.setPrototypeOf(this,Bk.prototype)}
r(Bk,Q);function Ck(a,b){Bk.call(this,"MISSING_OBJECT_STORES",{expectedObjectStores:b,foundObjectStores:a},wk.MISSING_OBJECT_STORES);Object.setPrototypeOf(this,Ck.prototype)}
r(Ck,Bk);function Dk(a,b){var c=Error.call(this);this.message=c.message;"stack"in c&&(this.stack=c.stack);this.index=a;this.objectStore=b;Object.setPrototypeOf(this,Dk.prototype)}
r(Dk,Error);var Ek=["The database connection is closing","Can't start a transaction on a closed database","A mutation operation was attempted on a database that did not allow mutations"];
function Fk(a,b,c,d){b=uk(b);var e=a instanceof Error?a:Error("Unexpected error: "+a);if(e instanceof Bk)return e;a={objectStoreNames:c,dbName:b,dbVersion:d};if("QuotaExceededError"===e.name)return new Bk("QUOTA_EXCEEDED",a);if(Jc&&"UnknownError"===e.name)return new Bk("QUOTA_MAYBE_EXCEEDED",a);if(e instanceof Dk)return new Bk("MISSING_INDEX",Object.assign({},a,{objectStore:e.objectStore,index:e.index}));if("InvalidStateError"===e.name&&Ek.some(function(f){return e.message.includes(f)}))return new Bk("EXECUTE_TRANSACTION_ON_CLOSED_DB",
a);
if("AbortError"===e.name)return new Bk("UNKNOWN_ABORT",a,e.message);e.args=[Object.assign({},a,{name:"IdbError",Cb:e.name})];e.level="WARNING";return e}
function Gk(a,b,c){var d=hk();return new Bk("IDB_NOT_SUPPORTED",{context:{caller:a,publicName:b,version:c,hasSucceededOnce:null==d?void 0:d.hasSucceededOnce}})}
;function Hk(a){if(!a)throw Error();throw a;}
function Ik(a){return a}
function Jk(a){this.h=a}
function Kk(a){function b(e){if("PENDING"===d.state.status){d.state={status:"REJECTED",reason:e};e=p(d.onRejected);for(var f=e.next();!f.done;f=e.next())f=f.value,f()}}
function c(e){if("PENDING"===d.state.status){d.state={status:"FULFILLED",value:e};e=p(d.h);for(var f=e.next();!f.done;f=e.next())f=f.value,f()}}
var d=this;this.state={status:"PENDING"};this.h=[];this.onRejected=[];a=a.h;try{a(c,b)}catch(e){b(e)}}
Kk.all=function(a){return new Kk(new Jk(function(b,c){var d=[],e=a.length;0===e&&b(d);for(var f={ma:0};f.ma<a.length;f={ma:f.ma},++f.ma)Lk(Kk.resolve(a[f.ma]).then(function(g){return function(h){d[g.ma]=h;e--;0===e&&b(d)}}(f)),function(g){c(g)})}))};
Kk.resolve=function(a){return new Kk(new Jk(function(b,c){a instanceof Kk?a.then(b,c):b(a)}))};
Kk.reject=function(a){return new Kk(new Jk(function(b,c){c(a)}))};
Kk.prototype.then=function(a,b){var c=this,d=null!=a?a:Ik,e=null!=b?b:Hk;return new Kk(new Jk(function(f,g){"PENDING"===c.state.status?(c.h.push(function(){Mk(c,c,d,f,g)}),c.onRejected.push(function(){Nk(c,c,e,f,g)})):"FULFILLED"===c.state.status?Mk(c,c,d,f,g):"REJECTED"===c.state.status&&Nk(c,c,e,f,g)}))};
function Lk(a,b){a.then(void 0,b)}
function Mk(a,b,c,d,e){try{if("FULFILLED"!==a.state.status)throw Error("calling handleResolve before the promise is fulfilled.");var f=c(a.state.value);f instanceof Kk?Ok(a,b,f,d,e):d(f)}catch(g){e(g)}}
function Nk(a,b,c,d,e){try{if("REJECTED"!==a.state.status)throw Error("calling handleReject before the promise is rejected.");var f=c(a.state.reason);f instanceof Kk?Ok(a,b,f,d,e):d(f)}catch(g){e(g)}}
function Ok(a,b,c,d,e){b===c?e(new TypeError("Circular promise chain detected.")):c.then(function(f){f instanceof Kk?Ok(a,b,f,d,e):d(f)},function(f){e(f)})}
;function Pk(a,b,c){function d(){c(a.error);f()}
function e(){b(a.result);f()}
function f(){try{a.removeEventListener("success",e),a.removeEventListener("error",d)}catch(g){}}
a.addEventListener("success",e);a.addEventListener("error",d)}
function Qk(a){return new Promise(function(b,c){Pk(a,b,c)})}
function Rk(a){return new Kk(new Jk(function(b,c){Pk(a,b,c)}))}
;function Sk(a,b){return new Kk(new Jk(function(c,d){function e(){var f=a?b(a):null;f?f.then(function(g){a=g;e()},d):c()}
e()}))}
;function Tk(a,b){this.h=a;this.options=b;this.transactionCount=0;this.j=Math.round(P());this.i=!1}
l=Tk.prototype;l.add=function(a,b,c){return Uk(this,[a],{mode:"readwrite",O:!0},function(d){return d.objectStore(a).add(b,c)})};
l.clear=function(a){return Uk(this,[a],{mode:"readwrite",O:!0},function(b){return b.objectStore(a).clear()})};
l.close=function(){this.h.close();var a;(null==(a=this.options)?0:a.closed)&&this.options.closed()};
l.count=function(a,b){return Uk(this,[a],{mode:"readonly",O:!0},function(c){return c.objectStore(a).count(b)})};
function Vk(a,b,c){a=a.h.createObjectStore(b,c);return new Wk(a)}
l.delete=function(a,b){return Uk(this,[a],{mode:"readwrite",O:!0},function(c){return c.objectStore(a).delete(b)})};
l.get=function(a,b){return Uk(this,[a],{mode:"readonly",O:!0},function(c){return c.objectStore(a).get(b)})};
function Xk(a,b){return Uk(a,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(c){c=c.objectStore("LogsRequestsStore");return Rk(c.h.put(b,void 0))})}
l.objectStoreNames=function(){return Array.from(this.h.objectStoreNames)};
function Uk(a,b,c,d){var e,f,g,h,k,m,q,u,C,v,E,F;return w(function(H){switch(H.h){case 1:var R={mode:"readonly",O:!1,tag:"IDB_TRANSACTION_TAG_UNKNOWN"};"string"===typeof c?R.mode=c:Object.assign(R,c);e=R;a.transactionCount++;f=e.O?3:1;g=0;case 2:if(h){H.s(3);break}g++;k=Math.round(P());wa(H,4);m=a.h.transaction(b,e.mode);R=new Yk(m);R=Zk(R,d);return t(H,R,6);case 6:return q=H.i,u=Math.round(P()),$k(a,k,u,g,void 0,b.join(),e),H.return(q);case 4:C=ya(H);v=Math.round(P());E=Fk(C,a.h.name,b.join(),a.h.version);
if((F=E instanceof Bk&&!E.h)||g>=f)$k(a,k,v,g,E,b.join(),e),h=E;H.s(2);break;case 3:return H.return(Promise.reject(h))}})}
function $k(a,b,c,d,e,f,g){b=c-b;e?(e instanceof Bk&&("QUOTA_EXCEEDED"===e.type||"QUOTA_MAYBE_EXCEEDED"===e.type)&&qk("QUOTA_EXCEEDED",{dbName:uk(a.h.name),objectStoreNames:f,transactionCount:a.transactionCount,transactionMode:g.mode}),e instanceof Bk&&"UNKNOWN_ABORT"===e.type&&(c-=a.j,0>c&&c>=Math.pow(2,31)&&(c=0),qk("TRANSACTION_UNEXPECTEDLY_ABORTED",{objectStoreNames:f,transactionDuration:b,transactionCount:a.transactionCount,dbDuration:c}),a.i=!0),al(a,!1,d,f,b,g.tag),pk(e)):al(a,!0,d,f,b,g.tag)}
function al(a,b,c,d,e,f){qk("TRANSACTION_ENDED",{objectStoreNames:d,connectionHasUnknownAbortedTransaction:a.i,duration:e,isSuccessful:b,tryCount:c,tag:void 0===f?"IDB_TRANSACTION_TAG_UNKNOWN":f})}
l.getName=function(){return this.h.name};
function Wk(a){this.h=a}
l=Wk.prototype;l.add=function(a,b){return Rk(this.h.add(a,b))};
l.autoIncrement=function(){return this.h.autoIncrement};
l.clear=function(){return Rk(this.h.clear()).then(function(){})};
l.count=function(a){return Rk(this.h.count(a))};
function bl(a,b){return cl(a,{query:b},function(c){return c.delete().then(function(){return c.continue()})}).then(function(){})}
l.delete=function(a){return a instanceof IDBKeyRange?bl(this,a):Rk(this.h.delete(a))};
l.get=function(a){return Rk(this.h.get(a))};
l.index=function(a){try{return new dl(this.h.index(a))}catch(b){if(b instanceof Error&&"NotFoundError"===b.name)throw new Dk(a,this.h.name);throw b;}};
l.getName=function(){return this.h.name};
l.keyPath=function(){return this.h.keyPath};
function cl(a,b,c){a=a.h.openCursor(b.query,b.direction);return el(a).then(function(d){return Sk(d,c)})}
function Yk(a){var b=this;this.h=a;this.j=new Map;this.i=!1;this.done=new Promise(function(c,d){b.h.addEventListener("complete",function(){c()});
b.h.addEventListener("error",function(e){e.currentTarget===e.target&&d(b.h.error)});
b.h.addEventListener("abort",function(){var e=b.h.error;if(e)d(e);else if(!b.i){e=Bk;for(var f=b.h.objectStoreNames,g=[],h=0;h<f.length;h++){var k=f.item(h);if(null===k)throw Error("Invariant: item in DOMStringList is null");g.push(k)}e=new e("UNKNOWN_ABORT",{objectStoreNames:g.join(),dbName:b.h.db.name,mode:b.h.mode});d(e)}})})}
function Zk(a,b){var c=new Promise(function(d,e){try{Lk(b(a).then(function(f){d(f)}),e)}catch(f){e(f),a.abort()}});
return Promise.all([c,a.done]).then(function(d){return p(d).next().value})}
Yk.prototype.abort=function(){this.h.abort();this.i=!0;throw new Bk("EXPLICIT_ABORT");};
Yk.prototype.objectStore=function(a){a=this.h.objectStore(a);var b=this.j.get(a);b||(b=new Wk(a),this.j.set(a,b));return b};
function dl(a){this.h=a}
l=dl.prototype;l.count=function(a){return Rk(this.h.count(a))};
l.delete=function(a){return fl(this,{query:a},function(b){return b.delete().then(function(){return b.continue()})})};
l.get=function(a){return Rk(this.h.get(a))};
l.getKey=function(a){return Rk(this.h.getKey(a))};
l.keyPath=function(){return this.h.keyPath};
l.unique=function(){return this.h.unique};
function fl(a,b,c){a=a.h.openCursor(void 0===b.query?null:b.query,void 0===b.direction?"next":b.direction);return el(a).then(function(d){return Sk(d,c)})}
function gl(a,b){this.request=a;this.cursor=b}
function el(a){return Rk(a).then(function(b){return b?new gl(a,b):null})}
l=gl.prototype;l.advance=function(a){this.cursor.advance(a);return el(this.request)};
l.continue=function(a){this.cursor.continue(a);return el(this.request)};
l.delete=function(){return Rk(this.cursor.delete()).then(function(){})};
l.getKey=function(){return this.cursor.key};
l.getValue=function(){return this.cursor.value};
l.update=function(a){return Rk(this.cursor.update(a))};function hl(a,b,c){return new Promise(function(d,e){function f(){C||(C=new Tk(g.result,{closed:u}));return C}
var g=void 0!==b?self.indexedDB.open(a,b):self.indexedDB.open(a);var h=c.blocked,k=c.blocking,m=c.Ac,q=c.upgrade,u=c.closed,C;g.addEventListener("upgradeneeded",function(v){try{if(null===v.newVersion)throw Error("Invariant: newVersion on IDbVersionChangeEvent is null");if(null===g.transaction)throw Error("Invariant: transaction on IDbOpenDbRequest is null");v.dataLoss&&"none"!==v.dataLoss&&qk("IDB_DATA_CORRUPTED",{reason:v.dataLossMessage||"unknown reason",dbName:uk(a)});var E=f(),F=new Yk(g.transaction);
q&&q(E,function(H){return v.oldVersion<H&&v.newVersion>=H},F);
F.done.catch(function(H){e(H)})}catch(H){e(H)}});
g.addEventListener("success",function(){var v=g.result;k&&v.addEventListener("versionchange",function(){k(f())});
v.addEventListener("close",function(){qk("IDB_UNEXPECTEDLY_CLOSED",{dbName:uk(a),dbVersion:v.version});m&&m()});
d(f())});
g.addEventListener("error",function(){e(g.error)});
h&&g.addEventListener("blocked",function(){h()})})}
function il(a,b,c){c=void 0===c?{}:c;return hl(a,b,c)}
function jl(a,b){b=void 0===b?{}:b;var c,d,e,f;return w(function(g){if(1==g.h)return wa(g,2),c=self.indexedDB.deleteDatabase(a),d=b,(e=d.blocked)&&c.addEventListener("blocked",function(){e()}),t(g,Qk(c),4);
if(2!=g.h)return xa(g,0);f=ya(g);throw Fk(f,a,"",-1);})}
;function kl(a){return new Promise(function(b){ak(function(){b()},a)})}
function ll(a,b){this.name=a;this.options=b;this.l=!0;this.m=this.o=0;this.i=500}
ll.prototype.j=function(a,b,c){c=void 0===c?{}:c;return il(a,b,c)};
ll.prototype.delete=function(a){a=void 0===a?{}:a;return jl(this.name,a)};
function ml(a,b){return new Bk("INCOMPATIBLE_DB_VERSION",{dbName:a.name,oldVersion:a.options.version,newVersion:b})}
function nl(a,b){if(!b)throw Gk("openWithToken",uk(a.name));return a.open()}
ll.prototype.open=function(){function a(){var f,g,h,k,m,q,u,C,v,E;return w(function(F){switch(F.h){case 1:return g=null!=(f=Error().stack)?f:"",wa(F,2),t(F,c.j(c.name,c.options.version,e),4);case 4:h=F.i;for(var H=c.options,R=[],O=p(Object.keys(H.xa)),S=O.next();!S.done;S=O.next()){S=S.value;var ka=H.xa[S],N=void 0===ka.jc?Number.MAX_VALUE:ka.jc;!(h.h.version>=ka.Va)||h.h.version>=N||h.h.objectStoreNames.contains(S)||R.push(S)}k=R;if(0===k.length){F.s(5);break}m=Object.keys(c.options.xa);q=h.objectStoreNames();
if(c.m<ci("ytidb_reopen_db_retries",0))return c.m++,h.close(),pk(new Bk("DB_REOPENED_BY_MISSING_OBJECT_STORES",{dbName:c.name,expectedObjectStores:m,foundObjectStores:q})),F.return(a());if(!(c.o<ci("ytidb_remake_db_retries",1))){F.s(6);break}c.o++;if(!M("ytidb_remake_db_enable_backoff_delay")){F.s(7);break}return t(F,kl(c.i),8);case 8:c.i*=2;case 7:return t(F,c.delete(),9);case 9:return pk(new Bk("DB_DELETED_BY_MISSING_OBJECT_STORES",{dbName:c.name,expectedObjectStores:m,foundObjectStores:q})),F.return(a());
case 6:throw new Ck(q,m);case 5:return F.return(h);case 2:u=ya(F);if(u instanceof DOMException?"VersionError"!==u.name:"DOMError"in self&&u instanceof DOMError?"VersionError"!==u.name:!(u instanceof Object&&"message"in u)||"An attempt was made to open a database using a lower version than the existing version."!==u.message){F.s(10);break}return t(F,c.j(c.name,void 0,Object.assign({},e,{upgrade:void 0})),11);case 11:C=F.i;v=C.h.version;if(void 0!==c.options.version&&v>c.options.version+1)throw C.close(),
c.l=!1,ml(c,v);return F.return(C);case 10:throw b(),u instanceof Error&&!M("ytidb_async_stack_killswitch")&&(u.stack=u.stack+"\n"+g.substring(g.indexOf("\n")+1)),Fk(u,c.name,"",null!=(E=c.options.version)?E:-1);}})}
function b(){c.h===d&&(c.h=void 0)}
var c=this;if(!this.l)throw ml(this);if(this.h)return this.h;var d,e={blocking:function(f){f.close()},
closed:b,Ac:b,upgrade:this.options.upgrade};return this.h=d=a()};var ol=new ll("YtIdbMeta",{xa:{databases:{Va:1}},upgrade:function(a,b){b(1)&&Vk(a,"databases",{keyPath:"actualName"})}});
function pl(a,b){var c;return w(function(d){if(1==d.h)return t(d,nl(ol,b),2);c=d.i;return d.return(Uk(c,["databases"],{O:!0,mode:"readwrite"},function(e){var f=e.objectStore("databases");return f.get(a.actualName).then(function(g){if(g?a.actualName!==g.actualName||a.publicName!==g.publicName||a.userIdentifier!==g.userIdentifier:1)return Rk(f.h.put(a,void 0)).then(function(){})})}))})}
function ql(a,b){var c;return w(function(d){if(1==d.h)return a?t(d,nl(ol,b),2):d.return();c=d.i;return d.return(c.delete("databases",a))})}
function rl(a,b){var c,d;return w(function(e){return 1==e.h?(c=[],t(e,nl(ol,b),2)):3!=e.h?(d=e.i,t(e,Uk(d,["databases"],{O:!0,mode:"readonly"},function(f){c.length=0;return cl(f.objectStore("databases"),{},function(g){a(g.getValue())&&c.push(g.getValue());return g.continue()})}),3)):e.return(c)})}
function sl(a){return rl(function(b){return"LogsDatabaseV2"===b.publicName&&void 0!==b.userIdentifier},a)}
function tl(a,b,c){return rl(function(d){return c?void 0!==d.userIdentifier&&!a.includes(d.userIdentifier)&&c.includes(d.publicName):void 0!==d.userIdentifier&&!a.includes(d.userIdentifier)},b)}
function ul(a){var b,c;return w(function(d){if(1==d.h)return b=sk("YtIdbMeta hasAnyMeta other"),t(d,rl(function(e){return void 0!==e.userIdentifier&&e.userIdentifier!==b},a),2);
c=d.i;return d.return(0<c.length)})}
;var vl,wl=new function(){}(new function(){});
function xl(){var a,b,c,d;return w(function(e){switch(e.h){case 1:a=hk();if(null==(b=a)?0:b.hasSucceededOnce)return e.return(!0);var f;if(f=ek)f=/WebKit\/([0-9]+)/.exec(Sb()),f=!!(f&&600<=parseInt(f[1],10));f&&(f=/WebKit\/([0-9]+)/.exec(Sb()),f=!(f&&602<=parseInt(f[1],10)));if(f||uc)return e.return(!1);try{if(c=self,!(c.indexedDB&&c.IDBIndex&&c.IDBKeyRange&&c.IDBObjectStore))return e.return(!1)}catch(g){return e.return(!1)}if(!("IDBTransaction"in self&&"objectStoreNames"in IDBTransaction.prototype))return e.return(!1);
wa(e,2);d={actualName:"yt-idb-test-do-not-use",publicName:"yt-idb-test-do-not-use",userIdentifier:void 0};return t(e,pl(d,wl),4);case 4:return t(e,ql("yt-idb-test-do-not-use",wl),5);case 5:return e.return(!0);case 2:return ya(e),e.return(!1)}})}
function yl(){if(void 0!==vl)return vl;kk=!0;return vl=xl().then(function(a){kk=!1;var b;if(null!=(b=gk())&&b.h){var c;b={hasSucceededOnce:(null==(c=hk())?void 0:c.hasSucceededOnce)||a};var d;null==(d=gk())||d.set("LAST_RESULT_ENTRY_KEY",b,2592E3,!0)}return a})}
function zl(){return z("ytglobal.idbToken_")||void 0}
function Al(){var a=zl();return a?Promise.resolve(a):yl().then(function(b){(b=b?wl:void 0)&&y("ytglobal.idbToken_",b,void 0);return b})}
;var Bl=0;function Cl(a,b){Bl||(Bl=bf.N(function(){var c,d,e,f,g;return w(function(h){switch(h.h){case 1:return t(h,Al(),2);case 2:c=h.i;if(!c)return h.return();d=!0;wa(h,3);return t(h,tl(a,c,b),5);case 5:e=h.i;if(!e.length){d=!1;h.s(6);break}f=e[0];return t(h,jl(f.actualName),7);case 7:return t(h,ql(f.actualName,c),6);case 6:xa(h,4);break;case 3:g=ya(h),pk(g),d=!1;case 4:bf.U(Bl),Bl=0,d&&Cl(a,b),h.h=0}})}))}
function Dl(){var a;return w(function(b){return 1==b.h?t(b,Al(),2):(a=b.i)?b.return(ul(a)):b.return(!1)})}
new Ad;function El(a){if(!rk())throw a=new Bk("AUTH_INVALID",{dbName:a}),pk(a),a;var b=sk();return{actualName:a+":"+b,publicName:a,userIdentifier:b}}
function Fl(a,b,c,d){var e,f,g,h,k,m;return w(function(q){switch(q.h){case 1:return f=null!=(e=Error().stack)?e:"",t(q,Al(),2);case 2:g=q.i;if(!g)throw h=Gk("openDbImpl",a,b),M("ytidb_async_stack_killswitch")||(h.stack=h.stack+"\n"+f.substring(f.indexOf("\n")+1)),pk(h),h;tk(a);k=c?{actualName:a,publicName:a,userIdentifier:void 0}:El(a);wa(q,3);return t(q,pl(k,g),5);case 5:return t(q,il(k.actualName,b,d),6);case 6:return q.return(q.i);case 3:return m=ya(q),wa(q,7),t(q,ql(k.actualName,g),9);case 9:xa(q,
8);break;case 7:ya(q);case 8:throw m;}})}
function Gl(a,b,c){c=void 0===c?{}:c;return Fl(a,b,!1,c)}
function Hl(a,b,c){c=void 0===c?{}:c;return Fl(a,b,!0,c)}
function Il(a,b){b=void 0===b?{}:b;var c,d;return w(function(e){if(1==e.h)return t(e,Al(),2);if(3!=e.h){c=e.i;if(!c)return e.return();tk(a);d=El(a);return t(e,jl(d.actualName,b),3)}return t(e,ql(d.actualName,c),0)})}
function Jl(a,b,c){a=a.map(function(d){return w(function(e){return 1==e.h?t(e,jl(d.actualName,b),2):t(e,ql(d.actualName,c),0)})});
return Promise.all(a).then(function(){})}
function Kl(){var a=void 0===a?{}:a;var b,c;return w(function(d){if(1==d.h)return t(d,Al(),2);if(3!=d.h){b=d.i;if(!b)return d.return();tk("LogsDatabaseV2");return t(d,sl(b),3)}c=d.i;return t(d,Jl(c,a,b),0)})}
function Ll(a,b){b=void 0===b?{}:b;var c;return w(function(d){if(1==d.h)return t(d,Al(),2);if(3!=d.h){c=d.i;if(!c)return d.return();tk(a);return t(d,jl(a,b),3)}return t(d,ql(a,c),0)})}
;function Ml(a){this.h=!1;this.potentialEsfErrorCounter=this.i=0;this.handleError=function(){};
this.qa=function(){};
this.now=Date.now;this.wa=!1;var b;this.Jb=null!=(b=a.Jb)?b:100;var c;this.Hb=null!=(c=a.Hb)?c:1;var d;this.Fb=null!=(d=a.Fb)?d:2592E6;var e;this.Db=null!=(e=a.Db)?e:12E4;var f;this.Gb=null!=(f=a.Gb)?f:5E3;var g;this.v=null!=(g=a.v)?g:void 0;this.Ka=!!a.Ka;var h;this.Ja=null!=(h=a.Ja)?h:.1;var k;this.Qa=null!=(k=a.Qa)?k:10;a.handleError&&(this.handleError=a.handleError);a.qa&&(this.qa=a.qa);a.wa&&(this.wa=a.wa);this.D=a.D;this.V=a.V;this.K=a.K;this.J=a.J;this.da=a.da;this.hb=a.hb;this.gb=a.gb;this.v&&
(!this.D||this.D("networkless_logging"))&&Nl(this)}
function Nl(a){a.v&&!a.wa&&(a.h=!0,a.Ka&&Math.random()<=a.Ja&&a.K.Qb(a.v),Ol(a),a.J.H()&&a.Aa(),a.J.W(a.hb,a.Aa.bind(a)),a.J.W(a.gb,a.mb.bind(a)))}
l=Ml.prototype;l.writeThenSend=function(a,b){var c=this;b=void 0===b?{}:b;if(this.v&&this.h){var d={url:a,options:b,timestamp:this.now(),status:"NEW",sendCount:0};this.K.set(d,this.v).then(function(e){d.id=e;c.J.H()&&Pl(c,d)}).catch(function(e){Pl(c,d);
Ql(c,e)})}else this.da(a,b)};
l.sendThenWrite=function(a,b,c){var d=this;b=void 0===b?{}:b;Promise.resolve().then(function(){Rl(d,a,b,c)})};
function Rl(a,b,c,d){c=void 0===c?{}:c;if(a.v&&a.h){var e={url:b,options:c,timestamp:a.now(),status:"NEW",sendCount:0};a.D&&a.D("nwl_skip_retry")&&(e.skipRetry=d);if(a.J.H()||a.D&&a.D("nwl_aggressive_send_then_write")&&!e.skipRetry){if(!e.skipRetry){var f=c.onError?c.onError:function(){};
c.onError=function(g,h){return w(function(k){if(1==k.h)return t(k,a.K.set(e,a.v).catch(function(m){Ql(a,m)}),2);
f(g,h);k.h=0})}}a.da(b,c,e.skipRetry)}else a.K.set(e,a.v).catch(function(g){a.da(b,c,e.skipRetry);
Ql(a,g)})}else a.da(b,c,a.D&&a.D("nwl_skip_retry")&&d)}
l.sendAndWrite=function(a,b){var c=this;b=void 0===b?{}:b;if(this.v&&this.h){var d={url:a,options:b,timestamp:this.now(),status:"NEW",sendCount:0},e=!1,f=b.onSuccess?b.onSuccess:function(){};
d.options.onSuccess=function(g,h){void 0!==d.id?c.K.oa(d.id,c.v):e=!0;c.J.ca&&c.D&&c.D("vss_network_hint")&&c.J.ca(!0);f(g,h)};
this.da(d.url,d.options);this.K.set(d,this.v).then(function(g){d.id=g;e&&c.K.oa(d.id,c.v)}).catch(function(g){Ql(c,g)})}else this.da(a,b)};
l.Aa=function(){var a=this;if(!this.v)throw Gk("throttleSend");this.i||(this.i=this.V.N(function(){var b;return w(function(c){if(1==c.h)return t(c,a.K.vb("NEW",a.v),2);if(3!=c.h)return b=c.i,b?t(c,Pl(a,b),3):(a.mb(),c.return());a.i&&(a.i=0,a.Aa());c.h=0})},this.Jb))};
l.mb=function(){this.V.U(this.i);this.i=0};
function Pl(a,b){var c,d;return w(function(e){switch(e.h){case 1:if(!a.v)throw c=Gk("immediateSend"),c;if(void 0===b.id){e.s(2);break}return t(e,a.K.ac(b.id,a.v),3);case 3:(d=e.i)?b=d:a.qa(Error("The request cannot be found in the database."));case 2:if(Sl(a,b,a.Fb)){e.s(4);break}a.qa(Error("Networkless Logging: Stored logs request expired age limit"));if(void 0===b.id){e.s(5);break}return t(e,a.K.oa(b.id,a.v),5);case 5:return e.return();case 4:b.skipRetry||(b=Tl(a,b));if(!b){e.s(0);break}if(!b.skipRetry||
void 0===b.id){e.s(8);break}return t(e,a.K.oa(b.id,a.v),8);case 8:a.da(b.url,b.options,!!b.skipRetry),e.h=0}})}
function Tl(a,b){if(!a.v)throw Gk("updateRequestHandlers");var c=b.options.onError?b.options.onError:function(){};
b.options.onError=function(e,f){var g,h,k;return w(function(m){switch(m.h){case 1:g=Ul(f);if(!(a.D&&a.D("nwl_consider_error_code")&&g||a.D&&!a.D("nwl_consider_error_code")&&a.potentialEsfErrorCounter<=a.Qa)){m.s(2);break}if(!a.J.ea){m.s(3);break}return t(m,a.J.ea(),3);case 3:if(a.J.H()){m.s(2);break}c(e,f);if(!a.D||!a.D("nwl_consider_error_code")||void 0===(null==(h=b)?void 0:h.id)){m.s(6);break}return t(m,a.K.ib(b.id,a.v,!1),6);case 6:return m.return();case 2:if(a.D&&a.D("nwl_consider_error_code")&&
!g&&a.potentialEsfErrorCounter>a.Qa)return m.return();a.potentialEsfErrorCounter++;if(void 0===(null==(k=b)?void 0:k.id)){m.s(8);break}return b.sendCount<a.Hb?t(m,a.K.ib(b.id,a.v),12):t(m,a.K.oa(b.id,a.v),8);case 12:a.V.N(function(){a.J.H()&&a.Aa()},a.Gb);
case 8:c(e,f),m.h=0}})};
var d=b.options.onSuccess?b.options.onSuccess:function(){};
b.options.onSuccess=function(e,f){var g;return w(function(h){if(1==h.h)return void 0===(null==(g=b)?void 0:g.id)?h.s(2):t(h,a.K.oa(b.id,a.v),2);a.J.ca&&a.D&&a.D("vss_network_hint")&&a.J.ca(!0);d(e,f);h.h=0})};
return b}
function Sl(a,b,c){b=b.timestamp;return a.now()-b>=c?!1:!0}
function Ol(a){if(!a.v)throw Gk("retryQueuedRequests");a.K.vb("QUEUED",a.v).then(function(b){b&&!Sl(a,b,a.Db)?a.V.N(function(){return w(function(c){if(1==c.h)return void 0===b.id?c.s(2):t(c,a.K.ib(b.id,a.v),2);Ol(a);c.h=0})}):a.J.H()&&a.Aa()})}
function Ql(a,b){a.Lb&&!a.J.H()?a.Lb(b):a.handleError(b)}
function Ul(a){var b;return(a=null==a?void 0:null==(b=a.error)?void 0:b.code)&&400<=a&&599>=a?!1:!0}
;function Vl(a,b){this.version=a;this.args=b}
;function Wl(a,b){this.topic=a;this.h=b}
Wl.prototype.toString=function(){return this.topic};var Xl=z("ytPubsub2Pubsub2Instance")||new L;L.prototype.subscribe=L.prototype.subscribe;L.prototype.unsubscribeByKey=L.prototype.ta;L.prototype.publish=L.prototype.ja;L.prototype.clear=L.prototype.clear;y("ytPubsub2Pubsub2Instance",Xl,void 0);var Yl=z("ytPubsub2Pubsub2SubscribedKeys")||{};y("ytPubsub2Pubsub2SubscribedKeys",Yl,void 0);var Zl=z("ytPubsub2Pubsub2TopicToKeys")||{};y("ytPubsub2Pubsub2TopicToKeys",Zl,void 0);var $l=z("ytPubsub2Pubsub2IsAsync")||{};y("ytPubsub2Pubsub2IsAsync",$l,void 0);
y("ytPubsub2Pubsub2SkipSubKey",null,void 0);function am(a,b){var c=bm();c&&c.publish.call(c,a.toString(),a,b)}
function cm(a){var b=dm,c=bm();if(!c)return 0;var d=c.subscribe(b.toString(),function(e,f){var g=z("ytPubsub2Pubsub2SkipSubKey");g&&g==d||(g=function(){if(Yl[d])try{if(f&&b instanceof Wl&&b!=e)try{var h=b.h,k=f;if(!k.args||!k.version)throw Error("yt.pubsub2.Data.deserialize(): serializedData is incomplete.");try{if(!h.ia){var m=new h;h.ia=m.version}var q=h.ia}catch(H){}if(!q||k.version!=q)throw Error("yt.pubsub2.Data.deserialize(): serializedData version is incompatible.");try{q=Reflect;var u=q.construct;
var C=k.args,v=C.length;if(0<v){var E=Array(v);for(k=0;k<v;k++)E[k]=C[k];var F=E}else F=[];f=u.call(q,h,F)}catch(H){throw H.message="yt.pubsub2.Data.deserialize(): "+H.message,H;}}catch(H){throw H.message="yt.pubsub2.pubsub2 cross-binary conversion error for "+b.toString()+": "+H.message,H;}a.call(window,f)}catch(H){ii(H)}},$l[b.toString()]?z("yt.scheduler.instance")?bf.N(g):Ci(g,0):g())});
Yl[d]=!0;Zl[b.toString()]||(Zl[b.toString()]=[]);Zl[b.toString()].push(d);return d}
function em(){var a=fm,b=cm(function(c){a.apply(void 0,arguments);gm(b)});
return b}
function gm(a){var b=bm();b&&("number"===typeof a&&(a=[a]),gb(a,function(c){b.unsubscribeByKey(c);delete Yl[c]}))}
function bm(){return z("ytPubsub2Pubsub2Instance")}
;function hm(a,b){ll.call(this,a,b);this.options=b;tk(a)}
r(hm,ll);function im(a,b){var c;return function(){c||(c=new hm(a,b));return c}}
hm.prototype.j=function(a,b,c){c=void 0===c?{}:c;return(this.options.jb?Hl:Gl)(a,b,Object.assign({},c))};
hm.prototype.delete=function(a){a=void 0===a?{}:a;return(this.options.jb?Ll:Il)(this.name,a)};
function jm(a,b){return im(a,b)}
;var km;
function lm(){if(km)return km();var a={};km=jm("LogsDatabaseV2",{xa:(a.LogsRequestsStore={Va:2},a),jb:!1,upgrade:function(b,c,d){c(2)&&Vk(b,"LogsRequestsStore",{keyPath:"id",autoIncrement:!0});c(3);c(5)&&(d=d.objectStore("LogsRequestsStore"),d.h.indexNames.contains("newRequest")&&d.h.deleteIndex("newRequest"),d.h.createIndex("newRequestV2",["status","interface","timestamp"],{unique:!1}));c(7)&&b.h.objectStoreNames.contains("sapisid")&&b.h.deleteObjectStore("sapisid");c(9)&&b.h.objectStoreNames.contains("SWHealthLog")&&b.h.deleteObjectStore("SWHealthLog")},
version:9});return km()}
;function mm(a){return nl(lm(),a)}
function nm(a,b){var c,d,e,f;return w(function(g){if(1==g.h)return c={startTime:P(),transactionType:"YT_IDB_TRANSACTION_TYPE_WRITE"},t(g,mm(b),2);if(3!=g.h)return d=g.i,e=Object.assign({},a,{options:JSON.parse(JSON.stringify(a.options)),interface:A("INNERTUBE_CONTEXT_CLIENT_NAME",0)}),t(g,Xk(d,e),3);f=g.i;c.Bc=P();om(c);return g.return(f)})}
function pm(a,b){var c,d,e,f,g,h,k;return w(function(m){if(1==m.h)return c={startTime:P(),transactionType:"YT_IDB_TRANSACTION_TYPE_READ"},t(m,mm(b),2);if(3!=m.h)return d=m.i,e=A("INNERTUBE_CONTEXT_CLIENT_NAME",0),f=[a,e,0],g=[a,e,P()],h=IDBKeyRange.bound(f,g),k=void 0,t(m,Uk(d,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(q){return fl(q.objectStore("LogsRequestsStore").index("newRequestV2"),{query:h,direction:"prev"},function(u){u.getValue()&&(k=u.getValue(),"NEW"===a&&(k.status="QUEUED",
u.update(k)))})}),3);
c.Bc=P();om(c);return m.return(k)})}
function qm(a,b){var c;return w(function(d){if(1==d.h)return t(d,mm(b),2);c=d.i;return d.return(Uk(c,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(e){var f=e.objectStore("LogsRequestsStore");return f.get(a).then(function(g){if(g)return g.status="QUEUED",Rk(f.h.put(g,void 0)).then(function(){return g})})}))})}
function rm(a,b,c){c=void 0===c?!0:c;var d;return w(function(e){if(1==e.h)return t(e,mm(b),2);d=e.i;return e.return(Uk(d,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(f){var g=f.objectStore("LogsRequestsStore");return g.get(a).then(function(h){return h?(h.status="NEW",c&&(h.sendCount+=1),Rk(g.h.put(h,void 0)).then(function(){return h})):Kk.resolve(void 0)})}))})}
function sm(a,b){var c;return w(function(d){if(1==d.h)return t(d,mm(b),2);c=d.i;return d.return(c.delete("LogsRequestsStore",a))})}
function tm(a){var b,c;return w(function(d){if(1==d.h)return t(d,mm(a),2);b=d.i;c=P()-2592E6;return t(d,Uk(b,["LogsRequestsStore"],{mode:"readwrite",O:!0},function(e){return cl(e.objectStore("LogsRequestsStore"),{},function(f){if(f.getValue().timestamp<=c)return f.delete().then(function(){return f.continue()})})}),0)})}
function um(){return w(function(a){return t(a,Kl(),0)})}
function om(a){M("nwl_csi_killswitch")||.01>=Math.random()&&am("nwl_transaction_latency_payload",a)}
;var vm={},wm=jm("ServiceWorkerLogsDatabase",{xa:(vm.SWHealthLog={Va:1},vm),jb:!0,upgrade:function(a,b){b(1)&&Vk(a,"SWHealthLog",{keyPath:"id",autoIncrement:!0}).h.createIndex("swHealthNewRequest",["interface","timestamp"],{unique:!1})},
version:1});function xm(a){return nl(wm(),a)}
function ym(a){var b,c;return w(function(d){if(1==d.h)return t(d,xm(a),2);b=d.i;c=P()-2592E6;return t(d,Uk(b,["SWHealthLog"],{mode:"readwrite",O:!0},function(e){return cl(e.objectStore("SWHealthLog"),{},function(f){if(f.getValue().timestamp<=c)return f.delete().then(function(){return f.continue()})})}),0)})}
function zm(a){var b;return w(function(c){if(1==c.h)return t(c,xm(a),2);b=c.i;return t(c,b.clear("SWHealthLog"),0)})}
;var Am={},Bm=0;
function Cm(a){var b=void 0===b?"":b;if(a)if(b)gj(a,void 0,"POST",b,void 0);else if(A("USE_NET_AJAX_FOR_PING_TRANSPORT",!1))gj(a,void 0,"GET","",void 0);else{b:{try{var c=new cb({url:a});if(c.j&&c.i||c.l){var d=cc(dc(5,a)),e;if(!(e=!d||!d.endsWith("/aclk"))){var f=a.search(kc),g=jc(a,0,"ri",f);if(0>g)var h=null;else{var k=a.indexOf("&",g);if(0>k||k>f)k=f;g+=3;h=decodeURIComponent(a.substr(g,k-g).replace(/\+/g," "))}e="1"!==h}var m=!e;break b}}catch(u){}m=!1}if(m){b:{try{if(window.navigator&&window.navigator.sendBeacon&&
window.navigator.sendBeacon(a,"")){var q=!0;break b}}catch(u){}q=!1}b=q?!0:!1}else b=!1;b||Dm(a)}}
function Dm(a){var b=new Image,c=""+Bm++;Am[c]=b;b.onload=b.onerror=function(){delete Am[c]};
b.src=a}
;function Em(){this.h=new Map;this.i=!1}
function Fm(){if(!Em.h){var a=z("yt.networkRequestMonitor.instance")||new Em;y("yt.networkRequestMonitor.instance",a,void 0);Em.h=a}return Em.h}
Em.prototype.requestComplete=function(a,b){b&&(this.i=!0);a=this.removeParams(a);this.h.get(a)||this.h.set(a,b)};
Em.prototype.isEndpointCFR=function(a){a=this.removeParams(a);return(a=this.h.get(a))?!1:!1===a&&this.i?!0:null};
Em.prototype.removeParams=function(a){return a.split("?")[0]};
Em.prototype.removeParams=Em.prototype.removeParams;Em.prototype.isEndpointCFR=Em.prototype.isEndpointCFR;Em.prototype.requestComplete=Em.prototype.requestComplete;Em.getInstance=Fm;var Gm;function Hm(){Gm||(Gm=new Pj("yt.offline"));return Gm}
function Im(a){if(M("offline_error_handling")){var b=Hm().get("errors",!0)||{};b[a.message]={name:a.name,stack:a.stack};a.level&&(b[a.message].level=a.level);Hm().set("errors",b,2592E3,!0)}}
function Jm(){if(M("offline_error_handling")){var a=Hm().get("errors",!0);if(a){for(var b in a)if(a[b]){var c=new Q(b,"sent via offline_errors");c.name=a[b].name;c.stack=a[b].stack;c.level=a[b].level;ii(c)}Hm().set("errors",{},2592E3,!0)}}}
;var Km=ci("network_polling_interval",3E4);function Lm(){Ve.call(this);var a=this;this.T=0;this.A=this.m=!1;this.j=this.Za();M("use_shared_nsm")?(this.i=af(),M("use_shared_nsm_and_keep_yt_online_updated")&&(this.i.W("networkstatus-online",function(){a.j=!0;a.A&&Jm()}),this.i.W("networkstatus-offline",function(){a.j=!1}))):(Mm(this),Nm(this))}
r(Lm,Ve);function Om(){if(!Lm.h){var a=z("yt.networkStatusManager.instance")||new Lm;y("yt.networkStatusManager.instance",a,void 0);Lm.h=a}return Lm.h}
l=Lm.prototype;l.H=function(){if(M("use_shared_nsm")&&this.i){var a;return null==(a=this.i)?void 0:a.H()}return this.j};
l.ca=function(a){if(M("use_shared_nsm")&&this.i){var b;null!=(b=this.i)&&(b.i=a)}else a!==this.j&&(this.j=a)};
l.cc=function(a){!M("use_shared_nsm")&&(this.m=!0,void 0===a?0:a)&&(this.T||Pm(this))};
l.Za=function(){var a=window.navigator.onLine;return void 0===a?!0:a};
l.Tb=function(){this.A=!0};
l.W=function(a,b){return M("use_shared_nsm")&&this.i?this.i.W(a,b):Ve.prototype.W.call(this,a,b)};
function Nm(a){window.addEventListener("online",function(){return w(function(b){if(1==b.h)return t(b,a.ea(),2);a.A&&Jm();b.h=0})})}
function Mm(a){window.addEventListener("offline",function(){return w(function(b){return t(b,a.ea(),0)})})}
function Pm(a){a.T=Yj(function(){return w(function(b){if(1==b.h)return a.j?a.Za()||!a.m?b.s(3):t(b,a.ea(),3):t(b,a.ea(),3);Pm(a);b.h=0})},Km)}
l.ea=function(a){var b=this;if(M("use_shared_nsm")&&this.i){var c=Ze(this.i,a);c.then(function(d){M("use_cfr_monitor")&&Fm().requestComplete("generate_204",d)});
return c}return this.u?this.u:this.u=new Promise(function(d){var e,f,g,h;return w(function(k){switch(k.h){case 1:return e=window.AbortController?new window.AbortController:void 0,g=null==(f=e)?void 0:f.signal,h=!1,wa(k,2,3),e&&(b.M=bf.N(function(){e.abort()},a||2E4)),t(k,fetch("/generate_204",{method:"HEAD",
signal:g}),5);case 5:h=!0;case 3:za(k);M("use_cfr_monitor")&&Fm().requestComplete("generate_204",h);b.u=void 0;b.M&&bf.U(b.M);h!==b.j&&(b.j=h,b.j&&b.m?We(b,"ytnetworkstatus-online"):b.m&&We(b,"ytnetworkstatus-offline"));d(h);Aa(k);break;case 2:ya(k),h=!1,k.s(3)}})})};
Lm.prototype.sendNetworkCheckRequest=Lm.prototype.ea;Lm.prototype.listen=Lm.prototype.W;Lm.prototype.enableErrorFlushing=Lm.prototype.Tb;Lm.prototype.getWindowStatus=Lm.prototype.Za;Lm.prototype.monitorNetworkStatusChange=Lm.prototype.cc;Lm.prototype.networkStatusHint=Lm.prototype.ca;Lm.prototype.isNetworkAvailable=Lm.prototype.H;Lm.getInstance=Om;function Qm(a){a=void 0===a?{}:a;Ve.call(this);var b=this;this.j=this.M=0;this.m="ytnetworkstatus-offline";this.u="ytnetworkstatus-online";M("use_shared_nsm")&&(this.m="networkstatus-offline",this.u="networkstatus-online");this.i=Om();var c=z("yt.networkStatusManager.instance.monitorNetworkStatusChange").bind(this.i);c&&c(a.sb);a.zb&&(c=z("yt.networkStatusManager.instance.enableErrorFlushing").bind(this.i))&&c();if(c=z("yt.networkStatusManager.instance.listen").bind(this.i))a.Sa?(this.Sa=a.Sa,c(this.u,
function(){Rm(b,"publicytnetworkstatus-online")}),c(this.m,function(){Rm(b,"publicytnetworkstatus-offline")})):(c(this.u,function(){We(b,"publicytnetworkstatus-online")}),c(this.m,function(){We(b,"publicytnetworkstatus-offline")}))}
r(Qm,Ve);Qm.prototype.H=function(){var a=z("yt.networkStatusManager.instance.isNetworkAvailable");return a?a.bind(this.i)():!0};
Qm.prototype.ca=function(a){var b=z("yt.networkStatusManager.instance.networkStatusHint").bind(this.i);b&&b(a)};
Qm.prototype.ea=function(a){var b=this,c;return w(function(d){c=z("yt.networkStatusManager.instance.sendNetworkCheckRequest").bind(b.i);return M("skip_network_check_if_cfr")&&Fm().isEndpointCFR("generate_204")?d.return(new Promise(function(e){var f;b.ca((null==(f=window.navigator)?void 0:f.onLine)||!0);e(b.H())})):c?d.return(c(a)):d.return(!0)})};
function Rm(a,b){a.Sa?a.j?(bf.U(a.M),a.M=bf.N(function(){a.A!==b&&(We(a,b),a.A=b,a.j=P())},a.Sa-(P()-a.j))):(We(a,b),a.A=b,a.j=P()):We(a,b)}
;var Sm;function Tm(){Ml.call(this,{K:{Qb:tm,oa:sm,vb:pm,ac:qm,ib:rm,set:nm},J:Um(),handleError:ii,qa:ji,da:Vm,now:P,Lb:Im,V:dk(),hb:"publicytnetworkstatus-online",gb:"publicytnetworkstatus-offline",Ka:!0,Ja:.1,Qa:ci("potential_esf_error_limit",10),D:M,wa:!(rk()&&Wm())});this.j=new Ad;M("networkless_immediately_drop_all_requests")&&um();Ll("LogsDatabaseV2")}
r(Tm,Ml);function Xm(){var a=z("yt.networklessRequestController.instance");a||(a=new Tm,y("yt.networklessRequestController.instance",a,void 0),M("networkless_logging")&&Al().then(function(b){a.v=b;Nl(a);a.j.resolve();a.Ka&&Math.random()<=a.Ja&&a.v&&ym(a.v);M("networkless_immediately_drop_sw_health_store")&&Ym(a)}));
return a}
Tm.prototype.writeThenSend=function(a,b){b||(b={});rk()||(this.h=!1);Ml.prototype.writeThenSend.call(this,a,b)};
Tm.prototype.sendThenWrite=function(a,b,c){b||(b={});rk()||(this.h=!1);Ml.prototype.sendThenWrite.call(this,a,b,c)};
Tm.prototype.sendAndWrite=function(a,b){b||(b={});rk()||(this.h=!1);Ml.prototype.sendAndWrite.call(this,a,b)};
Tm.prototype.awaitInitialization=function(){return this.j.promise};
function Ym(a){var b;w(function(c){if(!a.v)throw b=Gk("clearSWHealthLogsDb"),b;return c.return(zm(a.v).catch(function(d){a.handleError(d)}))})}
function Vm(a,b,c){M("use_cfr_monitor")&&Zm(a,b);var d;if(null==(d=b.postParams)?0:d.requestTimeMs)b.postParams.requestTimeMs=Math.round(P());c&&0===Object.keys(b).length?Cm(a):dj(a,b)}
function Um(){Sm||(Sm=new Qm({zb:!0,sb:!0}));return Sm}
function Zm(a,b){var c=b.onError?b.onError:function(){};
b.onError=function(e,f){Fm().requestComplete(a,!1);c(e,f)};
var d=b.onSuccess?b.onSuccess:function(){};
b.onSuccess=function(e,f){Fm().requestComplete(a,!0);d(e,f)}}
function Wm(){return M("embeds_web_nwl_disable_nocookie")?"www.youtube-nocookie.com"!==ec(document.location.toString()):!0}
;var $m=!1,an=0,bn=0,cn,dn=x.ytNetworklessLoggingInitializationOptions||{isNwlInitialized:$m,potentialEsfErrorCounter:bn};y("ytNetworklessLoggingInitializationOptions",dn,void 0);
function en(){var a;w(function(b){switch(b.h){case 1:return t(b,Al(),2);case 2:a=b.i;if(!a||!rk()&&!M("nwl_init_require_datasync_id_killswitch")||!Wm()){b.s(0);break}$m=!0;dn.isNwlInitialized=$m;if(!M("use_new_nwl_initialization")){b.s(4);break}return t(b,Xm().awaitInitialization(),5);case 5:return b.return();case 4:return t(b,Ll("LogsDatabaseV2"),6);case 6:if(!(.1>=Math.random())){b.s(7);break}return t(b,tm(a),8);case 8:return t(b,ym(a),7);case 7:fn();gn().H()&&hn();gn().W("publicytnetworkstatus-online",
hn);gn().W("publicytnetworkstatus-offline",jn);if(!M("networkless_immediately_drop_sw_health_store")){b.s(10);break}return t(b,kn(),10);case 10:if(M("networkless_immediately_drop_all_requests"))return t(b,um(),0);b.s(0)}})}
function ln(a,b){function c(d){var e=gn().H();if(!mn()||!d||e&&M("vss_networkless_bypass_write"))nn(a,b);else{var f={url:a,options:b,timestamp:P(),status:"NEW",sendCount:0};nm(f,d).then(function(g){f.id=g;gn().H()&&on(f)}).catch(function(g){on(f);
gn().H()?ii(g):Im(g)})}}
b=void 0===b?{}:b;M("skip_is_supported_killswitch")?Al().then(function(d){c(d)}):c(zl())}
function pn(a,b){function c(d){if(mn()&&d){var e={url:a,options:b,timestamp:P(),status:"NEW",sendCount:0},f=!1,g=b.onSuccess?b.onSuccess:function(){};
e.options.onSuccess=function(k,m){M("use_cfr_monitor")&&Fm().requestComplete(e.url,!0);void 0!==e.id?sm(e.id,d):f=!0;M("vss_network_hint")&&gn().ca(!0);g(k,m)};
if(M("use_cfr_monitor")){var h=b.onError?b.onError:function(){};
e.options.onError=function(k,m){Fm().requestComplete(e.url,!1);h(k,m)}}nn(e.url,e.options);
nm(e,d).then(function(k){e.id=k;f&&sm(e.id,d)}).catch(function(k){gn().H()?ii(k):Im(k)})}else nn(a,b)}
b=void 0===b?{}:b;M("skip_is_supported_killswitch")?Al().then(function(d){c(d)}):c(zl())}
function hn(){var a=zl();if(!a)throw Gk("throttleSend");an||(an=bf.N(function(){var b;return w(function(c){if(1==c.h)return t(c,pm("NEW",a),2);if(3!=c.h)return b=c.i,b?t(c,on(b),3):(jn(),c.return());an&&(an=0,hn());c.h=0})},100))}
function jn(){bf.U(an);an=0}
function on(a){var b,c,d;return w(function(e){switch(e.h){case 1:b=zl();if(!b)throw c=Gk("immediateSend"),c;if(void 0===a.id){e.s(2);break}return t(e,qm(a.id,b),3);case 3:(d=e.i)?a=d:ji(Error("The request cannot be found in the database."));case 2:if(qn(a,2592E6)){e.s(4);break}ji(Error("Networkless Logging: Stored logs request expired age limit"));if(void 0===a.id){e.s(5);break}return t(e,sm(a.id,b),5);case 5:return e.return();case 4:a.skipRetry||(a=rn(a));var f=a,g,h;if(null==f?0:null==(g=f.options)?
0:null==(h=g.postParams)?0:h.requestTimeMs)f.options.postParams.requestTimeMs=Math.round(P());a=f;if(!a){e.s(0);break}if(!a.skipRetry||void 0===a.id){e.s(8);break}return t(e,sm(a.id,b),8);case 8:nn(a.url,a.options,!!a.skipRetry),e.h=0}})}
function rn(a){var b=zl();if(!b)throw Gk("updateRequestHandlers");var c=a.options.onError?a.options.onError:function(){};
a.options.onError=function(e,f){var g,h,k;return w(function(m){switch(m.h){case 1:M("use_cfr_monitor")&&Fm().requestComplete(a.url,!1);g=Ul(f);if(!(M("nwl_consider_error_code")&&g||!M("nwl_consider_error_code")&&sn()<=ci("potential_esf_error_limit",10))){m.s(2);break}if(M("skip_checking_network_on_cfr_failure")&&(!M("skip_checking_network_on_cfr_failure")||Fm().isEndpointCFR(a.url))){m.s(3);break}return t(m,gn().ea(),3);case 3:if(gn().H()){m.s(2);break}c(e,f);if(!M("nwl_consider_error_code")||void 0===
(null==(h=a)?void 0:h.id)){m.s(6);break}return t(m,rm(a.id,b,!1),6);case 6:return m.return();case 2:if(M("nwl_consider_error_code")&&!g&&sn()>ci("potential_esf_error_limit",10))return m.return();z("ytNetworklessLoggingInitializationOptions")&&dn.potentialEsfErrorCounter++;bn++;if(void 0===(null==(k=a)?void 0:k.id)){m.s(8);break}return 1>a.sendCount?t(m,rm(a.id,b),12):t(m,sm(a.id,b),8);case 12:bf.N(function(){gn().H()&&hn()},5E3);
case 8:c(e,f),m.h=0}})};
var d=a.options.onSuccess?a.options.onSuccess:function(){};
a.options.onSuccess=function(e,f){var g;return w(function(h){if(1==h.h)return M("use_cfr_monitor")&&Fm().requestComplete(a.url,!0),void 0===(null==(g=a)?void 0:g.id)?h.s(2):t(h,sm(a.id,b),2);M("vss_network_hint")&&gn().ca(!0);d(e,f);h.h=0})};
return a}
function qn(a,b){a=a.timestamp;return P()-a>=b?!1:!0}
function fn(){var a=zl();if(!a)throw Gk("retryQueuedRequests");pm("QUEUED",a).then(function(b){b&&!qn(b,12E4)?bf.N(function(){return w(function(c){if(1==c.h)return void 0===b.id?c.s(2):t(c,rm(b.id,a),2);fn();c.h=0})}):gn().H()&&hn()})}
function kn(){var a,b;return w(function(c){a=zl();if(!a)throw b=Gk("clearSWHealthLogsDb"),b;return c.return(zm(a).catch(function(d){ii(d)}))})}
function gn(){if(M("use_new_nwl"))return Um();cn||(cn=new Qm({zb:!0,sb:!0}));return cn}
function nn(a,b,c){c&&0===Object.keys(b).length?Cm(a):dj(a,b)}
function mn(){return z("ytNetworklessLoggingInitializationOptions")?dn.isNwlInitialized:$m}
function sn(){return z("ytNetworklessLoggingInitializationOptions")?dn.potentialEsfErrorCounter:bn}
;function tn(a){var b=this;this.config_=null;a?this.config_=a:Ej()&&(this.config_=Fj());Yj(function(){Vj(b)},5E3)}
tn.prototype.isReady=function(){!this.config_&&Ej()&&(this.config_=Fj());return!!this.config_};
function Wj(a,b,c,d){function e(E){E=void 0===E?!1:E;var F;if(d.retry&&"www.youtube-nocookie.com"!=h&&(E||M("skip_ls_gel_retry")||"application/json"!==g.headers["Content-Type"]||(F=Tj(b,c,m,k)),F)){var H=g.onSuccess,R=g.onFetchSuccess;g.onSuccess=function(O,S){Uj(F);H(O,S)};
c.onFetchSuccess=function(O,S){Uj(F);R(O,S)}}try{E&&d.retry&&!d.Bb.bypassNetworkless?(g.method="POST",d.Bb.writeThenSend?M("use_new_nwl_wts")?Xm().writeThenSend(v,g):ln(v,g):M("use_new_nwl_saw")?Xm().sendAndWrite(v,g):pn(v,g)):(g.method="POST",g.postParams||(g.postParams={}),dj(v,g))}catch(O){if("InvalidAccessError"==O.name)F&&(Uj(F),F=0),ji(Error("An extension is blocking network request."));
else throw O;}F&&Yj(function(){Vj(a)},5E3)}
!A("VISITOR_DATA")&&"visitor_id"!==b&&.01>Math.random()&&ji(new Q("Missing VISITOR_DATA when sending innertube request.",b,c,d));if(!a.isReady()){var f=new Q("innertube xhrclient not ready",b,c,d);ii(f);throw f;}var g={headers:d.headers||{},method:"POST",postParams:c,postBody:d.postBody,postBodyFormat:d.postBodyFormat||"JSON",onTimeout:function(){d.onTimeout()},
onFetchTimeout:d.onTimeout,onSuccess:function(E,F){if(d.onSuccess)d.onSuccess(F)},
onFetchSuccess:function(E){if(d.onSuccess)d.onSuccess(E)},
onError:function(E,F){if(d.onError)d.onError(F)},
onFetchError:function(E){if(d.onError)d.onError(E)},
timeout:d.timeout,withCredentials:!0};g.headers["Content-Type"]||(g.headers["Content-Type"]="application/json");var h="";(f=a.config_.Xb)&&(h=f);var k=a.config_.Zb||!1,m=Nj(k,h,d);Object.assign(g.headers,m);(f=g.headers.Authorization)&&!h&&(g.headers["x-origin"]=window.location.origin);var q="/youtubei/"+a.config_.innertubeApiVersion+"/"+b,u={alt:"json"},C=a.config_.Yb&&f;C=C&&f.startsWith("Bearer");C||(u.key=a.config_.innertubeApiKey);var v=vi(""+h+q,u||{},!0);M("use_new_nwl")&&Xm().h||!M("use_new_nwl")&&
mn()?yl().then(function(E){e(E)}):e(!1)}
;var un={appSettingsCaptured:!0,visualElementAttached:!0,visualElementGestured:!0,visualElementHidden:!0,visualElementShown:!0,flowEvent:!0,visualElementStateChanged:!0,playbackAssociated:!0,youThere:!0,accountStateChangeSignedIn:!0,accountStateChangeSignedOut:!0},vn={latencyActionBaselined:!0,latencyActionInfo:!0,latencyActionTicked:!0,bedrockRepetitiveActionTimed:!0,adsClientStateChange:!0,streamzIncremented:!0,mdxDialAdditionalDataUpdateEvent:!0,tvhtml5WatchKeyEvent:!0,tvhtml5VideoSeek:!0,tokenRefreshEvent:!0,
adNotify:!0,adNotifyFilled:!0,tvhtml5LaunchUrlComponentChanged:!0,bedrockResourceConsumptionSnapshot:!0,deviceStartupMetrics:!0,mdxSignIn:!0,tvhtml5KeyboardLogging:!0,tvhtml5StartupSoundEvent:!0,tvhtml5LiveChatStatus:!0,tvhtml5DeviceStorageStatus:!0,tvhtml5LocalStorage:!0,directSignInEvent:!0,finalPayload:!0,tvhtml5SearchCompleted:!0,tvhtml5KeyboardPerformance:!0,adNotifyFailure:!0,latencyActionSpan:!0,tvhtml5AccountDialogOpened:!0,tvhtml5ApiTest:!0};var wn=0,xn=wc?"webkit":vc?"moz":tc?"ms":sc?"o":"";y("ytDomDomGetNextId",z("ytDomDomGetNextId")||function(){return++wn},void 0);var yn={stopImmediatePropagation:1,stopPropagation:1,preventMouseEvent:1,preventManipulation:1,preventDefault:1,layerX:1,layerY:1,screenX:1,screenY:1,scale:1,rotation:1,webkitMovementX:1,webkitMovementY:1};
function zn(a){this.type="";this.state=this.source=this.data=this.currentTarget=this.relatedTarget=this.target=null;this.charCode=this.keyCode=0;this.metaKey=this.shiftKey=this.ctrlKey=this.altKey=!1;this.rotation=this.clientY=this.clientX=0;this.scale=1;this.changedTouches=this.touches=null;try{if(a=a||window.event){this.event=a;for(var b in a)b in yn||(this[b]=a[b]);this.scale=a.scale;this.rotation=a.rotation;var c=a.target||a.srcElement;c&&3==c.nodeType&&(c=c.parentNode);this.target=c;var d=a.relatedTarget;
if(d)try{d=d.nodeName?d:null}catch(e){d=null}else"mouseover"==this.type?d=a.fromElement:"mouseout"==this.type&&(d=a.toElement);this.relatedTarget=d;this.clientX=void 0!=a.clientX?a.clientX:a.pageX;this.clientY=void 0!=a.clientY?a.clientY:a.pageY;this.keyCode=a.keyCode?a.keyCode:a.which;this.charCode=a.charCode||("keypress"==this.type?this.keyCode:0);this.altKey=a.altKey;this.ctrlKey=a.ctrlKey;this.shiftKey=a.shiftKey;this.metaKey=a.metaKey;this.h=a.pageX;this.i=a.pageY}}catch(e){}}
function An(a){if(document.body&&document.documentElement){var b=document.body.scrollTop+document.documentElement.scrollTop;a.h=a.clientX+(document.body.scrollLeft+document.documentElement.scrollLeft);a.i=a.clientY+b}}
zn.prototype.preventDefault=function(){this.event&&(this.event.returnValue=!1,this.event.preventDefault&&this.event.preventDefault())};
zn.prototype.stopPropagation=function(){this.event&&(this.event.cancelBubble=!0,this.event.stopPropagation&&this.event.stopPropagation())};
zn.prototype.stopImmediatePropagation=function(){this.event&&(this.event.cancelBubble=!0,this.event.stopImmediatePropagation&&this.event.stopImmediatePropagation())};var pb=x.ytEventsEventsListeners||{};y("ytEventsEventsListeners",pb,void 0);var Bn=x.ytEventsEventsCounter||{count:0};y("ytEventsEventsCounter",Bn,void 0);
function Cn(a,b,c,d){d=void 0===d?{}:d;a.addEventListener&&("mouseenter"!=b||"onmouseenter"in document?"mouseleave"!=b||"onmouseenter"in document?"mousewheel"==b&&"MozBoxSizing"in document.documentElement.style&&(b="MozMousePixelScroll"):b="mouseout":b="mouseover");return ob(function(e){var f="boolean"===typeof e[4]&&e[4]==!!d,g=Ra(e[4])&&Ra(d)&&vb(e[4],d);return!!e.length&&e[0]==a&&e[1]==b&&e[2]==c&&(f||g)})}
var Dn=eb(function(){var a=!1;try{var b=Object.defineProperty({},"capture",{get:function(){a=!0}});
window.addEventListener("test",null,b)}catch(c){}return a});
function En(a,b,c,d){d=void 0===d?{}:d;if(!a||!a.addEventListener&&!a.attachEvent)return"";var e=Cn(a,b,c,d);if(e)return e;e=++Bn.count+"";var f=!("mouseenter"!=b&&"mouseleave"!=b||!a.addEventListener||"onmouseenter"in document);var g=f?function(h){h=new zn(h);if(!Nd(h.relatedTarget,function(k){return k==a}))return h.currentTarget=a,h.type=b,c.call(a,h)}:function(h){h=new zn(h);
h.currentTarget=a;return c.call(a,h)};
g=hi(g);a.addEventListener?("mouseenter"==b&&f?b="mouseover":"mouseleave"==b&&f?b="mouseout":"mousewheel"==b&&"MozBoxSizing"in document.documentElement.style&&(b="MozMousePixelScroll"),Dn()||"boolean"===typeof d?a.addEventListener(b,g,d):a.addEventListener(b,g,!!d.capture)):a.attachEvent("on"+b,g);pb[e]=[a,b,c,g,d];return e}
function Fn(a){a&&("string"==typeof a&&(a=[a]),gb(a,function(b){if(b in pb){var c=pb[b],d=c[0],e=c[1],f=c[3];c=c[4];d.removeEventListener?Dn()||"boolean"===typeof c?d.removeEventListener(e,f,c):d.removeEventListener(e,f,!!c.capture):d.detachEvent&&d.detachEvent("on"+e,f);delete pb[b]}}))}
;var Gn=window.ytcsi&&window.ytcsi.now?window.ytcsi.now:window.performance&&window.performance.timing&&window.performance.now&&window.performance.timing.navigationStart?function(){return window.performance.timing.navigationStart+window.performance.now()}:function(){return(new Date).getTime()};function Hn(a){this.L=a;this.i=null;this.m=0;this.A=null;this.u=0;this.j=[];for(a=0;4>a;a++)this.j.push(0);this.l=0;this.T=En(window,"mousemove",Xa(this.Y,this));a=Xa(this.M,this);"function"===typeof a&&(a=hi(a));this.fa=window.setInterval(a,25)}
$a(Hn,K);Hn.prototype.Y=function(a){void 0===a.h&&An(a);var b=a.h;void 0===a.i&&An(a);this.i=new Jd(b,a.i)};
Hn.prototype.M=function(){if(this.i){var a=Gn();if(0!=this.m){var b=this.A,c=this.i,d=b.x-c.x;b=b.y-c.y;d=Math.sqrt(d*d+b*b)/(a-this.m);this.j[this.l]=.5<Math.abs((d-this.u)/this.u)?1:0;for(c=b=0;4>c;c++)b+=this.j[c]||0;3<=b&&this.L();this.u=d}this.m=a;this.A=this.i;this.l=(this.l+1)%4}};
Hn.prototype.I=function(){window.clearInterval(this.fa);Fn(this.T)};var In={};
function Jn(a){var b=void 0===a?{}:a;a=void 0===b.fc?!1:b.fc;b=void 0===b.Ub?!0:b.Ub;if(null==z("_lact",window)){var c=parseInt(A("LACT"),10);c=isFinite(c)?Date.now()-Math.max(c,0):-1;y("_lact",c,window);y("_fact",c,window);-1==c&&Kn();En(document,"keydown",Kn);En(document,"keyup",Kn);En(document,"mousedown",Kn);En(document,"mouseup",Kn);a?En(window,"touchmove",function(){Ln("touchmove",200)},{passive:!0}):(En(window,"resize",function(){Ln("resize",200)}),b&&En(window,"scroll",function(){Ln("scroll",200)}));
new Hn(function(){Ln("mouse",100)});
En(document,"touchstart",Kn,{passive:!0});En(document,"touchend",Kn,{passive:!0})}}
function Ln(a,b){In[a]||(In[a]=!0,bf.N(function(){Kn();In[a]=!1},b))}
function Kn(){null==z("_lact",window)&&Jn();var a=Date.now();y("_lact",a,window);-1==z("_fact",window)&&y("_fact",a,window);(a=z("ytglobal.ytUtilActivityCallback_"))&&a()}
function Mn(){var a=z("_lact",window);return null==a?-1:Math.max(Date.now()-a,0)}
;var Nn=x.ytPubsubPubsubInstance||new L,On=x.ytPubsubPubsubSubscribedKeys||{},Pn=x.ytPubsubPubsubTopicToKeys||{},Qn=x.ytPubsubPubsubIsSynchronous||{};function Rn(a,b){var c=Sn();if(c&&b){var d=c.subscribe(a,function(){var e=arguments;var f=function(){On[d]&&b.apply&&"function"==typeof b.apply&&b.apply(window,e)};
try{Qn[a]?f():Ci(f,0)}catch(g){ii(g)}},void 0);
On[d]=!0;Pn[a]||(Pn[a]=[]);Pn[a].push(d);return d}return 0}
function Tn(a){var b=Sn();b&&("number"===typeof a?a=[a]:"string"===typeof a&&(a=[parseInt(a,10)]),gb(a,function(c){b.unsubscribeByKey(c);delete On[c]}))}
function Un(a,b){var c=Sn();c&&c.publish.apply(c,arguments)}
function lo(a){var b=Sn();if(b)if(b.clear(a),a)Ko(a);else for(var c in Pn)Ko(c)}
function Sn(){return x.ytPubsubPubsubInstance}
function Ko(a){Pn[a]&&(a=Pn[a],gb(a,function(b){On[b]&&delete On[b]}),a.length=0)}
L.prototype.subscribe=L.prototype.subscribe;L.prototype.unsubscribeByKey=L.prototype.ta;L.prototype.publish=L.prototype.ja;L.prototype.clear=L.prototype.clear;y("ytPubsubPubsubInstance",Nn,void 0);y("ytPubsubPubsubTopicToKeys",Pn,void 0);y("ytPubsubPubsubIsSynchronous",Qn,void 0);y("ytPubsubPubsubSubscribedKeys",On,void 0);var Lo=ci("initial_gel_batch_timeout",2E3),Mo=Math.pow(2,16)-1,No=void 0;function Oo(){this.j=this.h=this.i=0}
var Po=new Oo,Qo=new Oo,Ro=!0,So=x.ytLoggingTransportGELQueue_||new Map;y("ytLoggingTransportGELQueue_",So,void 0);var To=x.ytLoggingTransportGELProtoQueue_||new Map;y("ytLoggingTransportGELProtoQueue_",To,void 0);var Uo=x.ytLoggingTransportTokensToCttTargetIds_||{};y("ytLoggingTransportTokensToCttTargetIds_",Uo,void 0);var Vo=x.ytLoggingTransportTokensToJspbCttTargetIds_||{};y("ytLoggingTransportTokensToJspbCttTargetIds_",Vo,void 0);
function Wo(a,b){if("log_event"===a.endpoint){var c=Xo(a),d=So.get(c)||[];So.set(c,d);d.push(a.payload);Yo(b,d,c)}}
function Zo(a,b){if("log_event"===a.endpoint){var c=Xo(a,!0),d=To.get(c)||[];To.set(c,d);a=td(a.payload);d.push(a);Yo(b,d,c,!0)}}
function Yo(a,b,c,d){d=void 0===d?!1:d;a&&(No=new a);a=ci("tvhtml5_logging_max_batch")||ci("web_logging_max_batch")||100;var e=P(),f=d?Qo.j:Po.j;b.length>=a?$o({writeThenSend:!0},M("flush_only_full_queue")?c:void 0,d):10<=e-f&&(ap(d),d?Qo.j=e:Po.j=e)}
function bp(a,b){if("log_event"===a.endpoint){var c=Xo(a),d=new Map;d.set(c,[a.payload]);b&&(No=new b);return new Zf(function(e){No&&No.isReady()?cp(d,e,{bypassNetworkless:!0},!0):e()})}}
function dp(a,b){if("log_event"===a.endpoint){var c=Xo(a,!0),d=new Map;d.set(c,[td(a.payload)]);b&&(No=new b);return new Zf(function(e){No&&No.isReady()?ep(d,e,{bypassNetworkless:!0},!0):e()})}}
function Xo(a,b){var c="";if(a.va)c="visitorOnlyApprovedKey";else if(a.cttAuthInfo){if(void 0===b?0:b){b=a.cttAuthInfo.token;c=a.cttAuthInfo;var d=new Gh;c.videoId?d.setVideoId(c.videoId):c.playlistId&&kd(d,2,Hh,c.playlistId);Vo[b]=d}else b=a.cttAuthInfo,c={},b.videoId?c.videoId=b.videoId:b.playlistId&&(c.playlistId=b.playlistId),Uo[a.cttAuthInfo.token]=c;c=a.cttAuthInfo.token}return c}
function $o(a,b,c){a=void 0===a?{}:a;c=void 0===c?!1:c;new Zf(function(d){c?(Di(Qo.i),Di(Qo.h),Qo.h=0):(Di(Po.i),Di(Po.h),Po.h=0);if(No&&No.isReady())if(void 0!==b)if(c){var e=new Map,f=To.get(b)||[];e.set(b,f);ep(e,d,a);To.delete(b)}else e=new Map,f=So.get(b)||[],e.set(b,f),cp(e,d,a),So.delete(b);else c?(ep(To,d,a),To.clear()):(cp(So,d,a),So.clear());else ap(c),d()})}
function ap(a){a=void 0===a?!1:a;if(M("web_gel_timeout_cap")&&(!a&&!Po.h||a&&!Qo.h)){var b=Ci(function(){$o({writeThenSend:!0},void 0,a)},6E4);
a?Qo.h=b:Po.h=b}Di(a?Qo.i:Po.i);b=A("LOGGING_BATCH_TIMEOUT",ci("web_gel_debounce_ms",1E4));M("shorten_initial_gel_batch_timeout")&&Ro&&(b=Lo);b=Ci(function(){$o({writeThenSend:!0},void 0,a)},b);
a?Qo.i=b:Po.i=b}
function cp(a,b,c,d){var e=No;c=void 0===c?{}:c;var f=Math.round(P()),g=a.size;a=p(a);for(var h=a.next();!h.done;h=a.next()){var k=p(h.value);h=k.next().value;var m=k=k.next().value;k=xb({context:Gj(e.config_||Fj())});k.events=m;(m=Uo[h])&&fp(k,h,m);delete Uo[h];h="visitorOnlyApprovedKey"===h;gp(k,f,h);hp(c);Wj(e,"log_event",k,ip(c,h,function(){g--;g||b()},function(){g--;
g||b()},d));
Ro=!1}}
function ep(a,b,c,d){var e=No;c=void 0===c?{}:c;var f=Math.round(P()),g=a.size;a=p(a);for(var h=a.next();!h.done;h=a.next()){var k=p(h.value);h=k.next().value;var m=k=k.next().value;k=new Ih;var q=Mj(e.config_||Fj());I(k,1,q);m=jp(m);for(q=0;q<m.length;q++)pd(k,3,Ch,m[q]);(m=Vo[h])&&kp(k,h,m);delete Vo[h];h="visitorOnlyApprovedKey"===h;lp(k,f,h);hp(c);k=td(k);h=ip(c,h,function(){g--;g||b()},function(){g--;
g||b()},d);
h.headers={"Content-Type":"application/json+protobuf"};h.postBodyFormat="JSPB";h.postBody=k;Wj(e,"log_event","",h);Ro=!1}}
function hp(a){M("always_send_and_write")&&(a.writeThenSend=!1)}
function ip(a,b,c,d,e){return{retry:!0,onSuccess:c,onError:d,Bb:a,va:b,Oo:!!e,headers:{},postBodyFormat:"",postBody:""}}
function gp(a,b,c){a.requestTimeMs=String(b);M("unsplit_gel_payloads_in_logs")&&(a.unsplitGelPayloadsInLogs=!0);!c&&(b=A("EVENT_ID",void 0))&&(c=mp(),a.serializedClientEventId={serializedEventId:b,clientCounter:String(c)})}
function lp(a,b,c){D(a,2,b);if(!c&&(b=A("EVENT_ID",void 0))){c=mp();var d=new Fh;D(d,1,b);D(d,2,c);I(a,5,d)}}
function mp(){var a=A("BATCH_CLIENT_COUNTER",void 0)||0;a||(a=Math.floor(Math.random()*Mo/2));a++;a>Mo&&(a=1);Zh("BATCH_CLIENT_COUNTER",a);return a}
function fp(a,b,c){if(c.videoId)var d="VIDEO";else if(c.playlistId)d="PLAYLIST";else return;a.credentialTransferTokenTargetId=c;a.context=a.context||{};a.context.user=a.context.user||{};a.context.user.credentialTransferTokens=[{token:b,scope:d}]}
function kp(a,b,c){if(id(c,1===ld(c,Hh)?1:-1))var d=1;else if(c.getPlaylistId())d=2;else return;I(a,4,c);a=md(a,Tg,1)||new Tg;c=md(a,Rg,3)||new Rg;var e=new Qg;e.setToken(b);D(e,1,d);pd(c,12,Qg,e);I(a,3,c)}
function jp(a){for(var b=[],c=0;c<a.length;c++)try{var d=b,e=d.push;var f=String(a[c]),g=Ch;if(null==f||""==f)var h=new g;else{var k=JSON.parse(f);if(!Array.isArray(k))throw Error("Expected to deserialize an Array but got "+Pa(k)+": "+k);sd=k;var m=new g(k);sd=null;h=m}e.call(d,h)}catch(q){ii(new Q("Transport failed to deserialize "+String(a[c])))}return b}
;var np=x.ytLoggingGelSequenceIdObj_||{};y("ytLoggingGelSequenceIdObj_",np,void 0);
function op(a,b,c,d){d=void 0===d?{}:d;if(M("lr_drop_other_and_business_payloads")){if(vn[a]||un[a])return}else if(M("lr_drop_other_payloads")&&vn[a])return;var e={},f=Math.round(d.timestamp||P());e.eventTimeMs=f<Number.MAX_SAFE_INTEGER?f:0;e[a]=b;a=Mn();e.context={lastActivityMs:String(d.timestamp||!isFinite(a)?-1:a)};M("log_sequence_info_on_gel_web")&&d.X&&(a=e.context,b=d.X,b={index:pp(b),groupKey:b},a.sequence=b,d.tb&&delete np[d.X]);(d.oc?bp:Wo)({endpoint:"log_event",payload:e,cttAuthInfo:d.cttAuthInfo,
va:d.va},c)}
function pp(a){np[a]=a in np?np[a]+1:0;return np[a]}
;function ok(a,b,c){c=void 0===c?{}:c;var d=tn;A("ytLoggingEventsDefaultDisabled",!1)&&tn==tn&&(d=null);op(a,b,d,c)}
;var qp=[{fb:function(a){return"Cannot read property '"+a.key+"'"},
Pa:{Error:[{regexp:/(Permission denied) to access property "([^']+)"/,groups:["reason","key"]}],TypeError:[{regexp:/Cannot read property '([^']+)' of (null|undefined)/,groups:["key","value"]},{regexp:/\u65e0\u6cd5\u83b7\u53d6\u672a\u5b9a\u4e49\u6216 (null|undefined) \u5f15\u7528\u7684\u5c5e\u6027\u201c([^\u201d]+)\u201d/,groups:["value","key"]},{regexp:/\uc815\uc758\ub418\uc9c0 \uc54a\uc74c \ub610\ub294 (null|undefined) \ucc38\uc870\uc778 '([^']+)' \uc18d\uc131\uc744 \uac00\uc838\uc62c \uc218 \uc5c6\uc2b5\ub2c8\ub2e4./,
groups:["value","key"]},{regexp:/No se puede obtener la propiedad '([^']+)' de referencia nula o sin definir/,groups:["key"]},{regexp:/Unable to get property '([^']+)' of (undefined or null) reference/,groups:["key","value"]},{regexp:/(null) is not an object \(evaluating '(?:([^.]+)\.)?([^']+)'\)/,groups:["value","base","key"]}]}},{fb:function(a){return"Cannot call '"+a.key+"'"},
Pa:{TypeError:[{regexp:/(?:([^ ]+)?\.)?([^ ]+) is not a function/,groups:["base","key"]},{regexp:/([^ ]+) called on (null or undefined)/,groups:["key","value"]},{regexp:/Object (.*) has no method '([^ ]+)'/,groups:["base","key"]},{regexp:/Object doesn't support property or method '([^ ]+)'/,groups:["key"]},{regexp:/\u30aa\u30d6\u30b8\u30a7\u30af\u30c8\u306f '([^']+)' \u30d7\u30ed\u30d1\u30c6\u30a3\u307e\u305f\u306f\u30e1\u30bd\u30c3\u30c9\u3092\u30b5\u30dd\u30fc\u30c8\u3057\u3066\u3044\u307e\u305b\u3093/,
groups:["key"]},{regexp:/\uac1c\uccb4\uac00 '([^']+)' \uc18d\uc131\uc774\ub098 \uba54\uc11c\ub4dc\ub97c \uc9c0\uc6d0\ud558\uc9c0 \uc54a\uc2b5\ub2c8\ub2e4./,groups:["key"]}]}},{fb:function(a){return a.key+" is not defined"},
Pa:{ReferenceError:[{regexp:/(.*) is not defined/,groups:["key"]},{regexp:/Can't find variable: (.*)/,groups:["key"]}]}}];var sp={ha:[],ga:[{ka:rp,weight:500}]};function rp(a){if("JavaException"===a.name)return!0;a=a.stack;return a.includes("chrome://")||a.includes("chrome-extension://")||a.includes("moz-extension://")}
;function tp(){this.ga=[];this.ha=[]}
var up;function vp(){if(!up){var a=up=new tp;a.ha.length=0;a.ga.length=0;sp.ha&&a.ha.push.apply(a.ha,sp.ha);sp.ga&&a.ga.push.apply(a.ga,sp.ga)}return up}
;var wp=new L;function xp(a){function b(){return a.charCodeAt(d++)}
var c=a.length,d=0;do{var e=yp(b);if(Infinity===e)break;var f=e>>3;switch(e&7){case 0:e=yp(b);if(2===f)return e;break;case 1:if(2===f)return;d+=8;break;case 2:e=yp(b);if(2===f)return a.substr(d,e);d+=e;break;case 5:if(2===f)return;d+=4;break;default:return}}while(d<c)}
function yp(a){var b=a(),c=b&127;if(128>b)return c;b=a();c|=(b&127)<<7;if(128>b)return c;b=a();c|=(b&127)<<14;if(128>b)return c;b=a();return 128>b?c|(b&127)<<21:Infinity}
;function zp(a,b,c,d){if(a)if(Array.isArray(a)){var e=d;for(d=0;d<a.length&&!(a[d]&&(e+=Ap(d,a[d],b,c),500<e));d++);d=e}else if("object"===typeof a)for(e in a){if(a[e]){var f=a[e];var g=b;var h=c;g="string"!==typeof f||"clickTrackingParams"!==e&&"trackingParams"!==e?0:(f=xp(atob(f.replace(/-/g,"+").replace(/_/g,"/"))))?Ap(e+".ve",f,g,h):0;d+=g;d+=Ap(e,a[e],b,c);if(500<d)break}}else c[b]=Bp(a),d+=c[b].length;else c[b]=Bp(a),d+=c[b].length;return d}
function Ap(a,b,c,d){c+="."+a;a=Bp(b);d[c]=a;return c.length+a.length}
function Bp(a){try{return("string"===typeof a?a:String(JSON.stringify(a))).substr(0,500)}catch(b){return"unable to serialize "+typeof a+" ("+b.message+")"}}
;var Cp=x.ytLoggingGelSequenceIdObj_||{};y("ytLoggingGelSequenceIdObj_",Cp,void 0);function Dp(a,b,c){c=void 0===c?{}:c;var d=Math.round(c.timestamp||P());D(a,1,d<Number.MAX_SAFE_INTEGER?d:0);var e=Mn();d=new Bh;D(d,1,c.timestamp||!isFinite(e)?-1:e);if(M("log_sequence_info_on_gel_web")&&c.X){e=c.X;var f=pp(e),g=new Ah;D(g,2,f);D(g,1,e);I(d,3,g);c.tb&&delete Cp[c.X]}I(a,33,d);(c.oc?dp:Zo)({endpoint:"log_event",payload:a,cttAuthInfo:c.cttAuthInfo,va:c.va},b)}
;function Ep(a,b){b=void 0===b?{}:b;var c=!1;A("ytLoggingEventsDefaultDisabled",!1)&&tn===tn&&(c=!0);Dp(a,c?null:tn,b)}
;function Fp(a,b,c){var d=new Ch;od(d,72,Dh,a);c?Dp(d,c,b):Ep(d,b)}
function Gp(a,b,c){var d=new Ch;od(d,73,Dh,a);c?Dp(d,c,b):Ep(d,b)}
function Hp(a,b,c){var d=new Ch;od(d,78,Dh,a);c?Dp(d,c,b):Ep(d,b)}
function Ip(a,b,c){var d=new Ch;od(d,208,Dh,a);c?Dp(d,c,b):Ep(d,b)}
function Jp(a,b,c){var d=new Ch;od(d,156,Dh,a);c?Dp(d,c,b):Ep(d,b)}
function Kp(a,b,c){var d=new Ch;od(d,215,Dh,a);c?Dp(d,c,b):Ep(d,b)}
function Lp(a,b,c){var d=new Ch;od(d,111,Dh,a);c?Dp(d,c,b):Ep(d,b)}
;var Mp=new Set,Np=0,Op=0,Pp=0,Qp=[],Rp=["PhantomJS","Googlebot","TO STOP THIS SECURITY SCAN go/scan"];function nk(a){Sp(a)}
function Tp(a){Sp(a,"WARNING")}
function Sp(a,b,c,d,e,f){f=void 0===f?{}:f;f.name=c||A("INNERTUBE_CONTEXT_CLIENT_NAME",1);f.version=d||A("INNERTUBE_CONTEXT_CLIENT_VERSION",void 0);var g=f||{},h=void 0===b?"ERROR":b;h=void 0===h?"ERROR":h;if(a){a.hasOwnProperty("level")&&a.level&&(h=a.level);if(M("console_log_js_exceptions")){var k=[];k.push("Name: "+a.name);k.push("Message: "+a.message);a.hasOwnProperty("params")&&k.push("Error Params: "+JSON.stringify(a.params));a.hasOwnProperty("args")&&k.push("Error args: "+JSON.stringify(a.args));
k.push("File name: "+a.fileName);k.push("Stacktrace: "+a.stack);window.console.log(k.join("\n"),a)}if(!(5<=Np)){var m=Qp,q=te(a),u=q.message||"Unknown Error",C=q.name||"UnknownError",v=q.stack||a.i||"Not available";if(v.startsWith(C+": "+u)){var E=v.split("\n");E.shift();v=E.join("\n")}var F=q.lineNumber||"Not available",H=q.fileName||"Not available",R=v,O=0;if(a.hasOwnProperty("args")&&a.args&&a.args.length)for(var S=0;S<a.args.length&&!(O=zp(a.args[S],"params."+S,g,O),500<=O);S++);else if(a.hasOwnProperty("params")&&
a.params){var ka=a.params;if("object"===typeof a.params)for(var N in ka){if(ka[N]){var Ba="params."+N,Oa=Bp(ka[N]);g[Ba]=Oa;O+=Ba.length+Oa.length;if(500<O)break}}else g.params=Bp(ka)}if(m.length)for(var ua=0;ua<m.length&&!(O=zp(m[ua],"params.context."+ua,g,O),500<=O);ua++);navigator.vendor&&!g.hasOwnProperty("vendor")&&(g["device.vendor"]=navigator.vendor);var G={message:u,name:C,lineNumber:F,fileName:H,stack:R,params:g,sampleWeight:1},Ca=Number(a.columnNumber);isNaN(Ca)||(G.lineNumber=G.lineNumber+
":"+Ca);if("IGNORED"===a.level)var ta=0;else a:{for(var Vn=vp(),Wn=p(Vn.ha),Ei=Wn.next();!Ei.done;Ei=Wn.next()){var Xn=Ei.value;if(G.message&&G.message.match(Xn.To)){ta=Xn.weight;break a}}for(var Yn=p(Vn.ga),Fi=Yn.next();!Fi.done;Fi=Yn.next()){var Zn=Fi.value;if(Zn.ka(G)){ta=Zn.weight;break a}}ta=1}G.sampleWeight=ta;for(var $n=p(qp),Gi=$n.next();!Gi.done;Gi=$n.next()){var Hi=Gi.value;if(Hi.Pa[G.name])for(var ao=p(Hi.Pa[G.name]),Ii=ao.next();!Ii.done;Ii=ao.next()){var bo=Ii.value,Qf=G.message.match(bo.regexp);
if(Qf){G.params["params.error.original"]=Qf[0];for(var Ji=bo.groups,co={},ad=0;ad<Ji.length;ad++)co[Ji[ad]]=Qf[ad+1],G.params["params.error."+Ji[ad]]=Qf[ad+1];G.message=Hi.fb(co);break}}}G.params||(G.params={});var eo=vp();G.params["params.errorServiceSignature"]="msg="+eo.ha.length+"&cb="+eo.ga.length;G.params["params.serviceWorker"]="false";x.document&&x.document.querySelectorAll&&(G.params["params.fscripts"]=String(document.querySelectorAll("script:not([nonce])").length));Eb("sample").constructor!==
Cb&&(G.params["params.fconst"]="true");window.yterr&&"function"===typeof window.yterr&&window.yterr(G);if(0!==G.sampleWeight&&!Mp.has(G.message)){if("ERROR"===h){wp.ja("handleError",G);if(M("record_app_crashed_web")&&0===Pp&&1===G.sampleWeight)if(Pp++,M("errors_via_jspb")){var Ki=new fh;D(Ki,1,1);if(!M("report_client_error_with_app_crash_ks")){var fo=new ah;D(fo,1,G.message);var go=new bh;I(go,3,fo);var ho=new ch;I(ho,5,go);var io=new dh;I(io,9,ho);I(Ki,4,io)}var jo=new Ch;od(jo,20,Dh,Ki);Ep(jo,void 0)}else{var ko=
{appCrashType:"APP_CRASH_TYPE_BREAKPAD"};M("report_client_error_with_app_crash_ks")||(ko.systemHealth={crashData:{clientError:{logMessage:{message:G.message}}}});ok("appCrashed",ko)}Op++}else"WARNING"===h&&wp.ja("handleWarning",G);if(M("kevlar_gel_error_routing"))a:{var $d=h;if(M("errors_via_jspb")){if(Up())var mo=void 0;else{var bd=new Yg;D(bd,1,G.stack);G.fileName&&D(bd,4,G.fileName);var rb=G.lineNumber&&G.lineNumber.split?G.lineNumber.split(":"):[];0!==rb.length&&(1!==rb.length||isNaN(Number(rb[0]))?
2!==rb.length||isNaN(Number(rb[0]))||isNaN(Number(rb[1]))||(D(bd,2,Number(rb[0])),D(bd,3,Number(rb[1]))):D(bd,2,Number(rb[0])));var lc=new ah;D(lc,1,G.message);D(lc,3,G.name);D(lc,6,G.sampleWeight);"ERROR"===$d?D(lc,2,2):"WARNING"===$d?D(lc,2,1):D(lc,2,0);var Li=new Zg;D(Li,1,!0);od(Li,3,$g,bd);var Mb=new Vg;D(Mb,3,window.location.href);for(var no=A("FEXP_EXPERIMENTS",[]),Mi=0;Mi<no.length;Mi++){var Gt=no[Mi];Xc(Mb);jd(Mb,5).push(Gt)}var Ni=A("LATEST_ECATCHER_SERVICE_TRACKING_PARAMS",void 0);if(!ai()&&
Ni)for(var oo=p(Object.keys(Ni)),mc=oo.next();!mc.done;mc=oo.next()){var po=mc.value,Oi=new Xg;D(Oi,1,po);Oi.setValue(String(Ni[po]));pd(Mb,4,Xg,Oi)}var Pi=G.params;if(Pi){var qo=p(Object.keys(Pi));for(mc=qo.next();!mc.done;mc=qo.next()){var ro=mc.value,Qi=new Xg;D(Qi,1,"client."+ro);Qi.setValue(String(Pi[ro]));pd(Mb,4,Xg,Qi)}}var so=$h("SERVER_NAME"),to=$h("SERVER_VERSION");if(so&&to){var Ri=new Xg;D(Ri,1,"server.name");Ri.setValue(so);pd(Mb,4,Xg,Ri);var Si=new Xg;D(Si,1,"server.version");Si.setValue(to);
pd(Mb,4,Xg,Si)}var Rf=new bh;I(Rf,1,Mb);I(Rf,2,Li);I(Rf,3,lc);mo=Rf}var uo=mo;if(!uo)break a;var vo=new Ch;od(vo,163,Dh,uo);Ep(vo,void 0)}else{if(Up())var wo=void 0;else{var ae={stackTrace:G.stack};G.fileName&&(ae.filename=G.fileName);var sb=G.lineNumber&&G.lineNumber.split?G.lineNumber.split(":"):[];0!==sb.length&&(1!==sb.length||isNaN(Number(sb[0]))?2!==sb.length||isNaN(Number(sb[0]))||isNaN(Number(sb[1]))||(ae.lineNumber=Number(sb[0]),ae.columnNumber=Number(sb[1])):ae.lineNumber=Number(sb[0]));
var Ti={level:"ERROR_LEVEL_UNKNOWN",message:G.message,errorClassName:G.name,sampleWeight:G.sampleWeight};"ERROR"===$d?Ti.level="ERROR_LEVEL_ERROR":"WARNING"===$d&&(Ti.level="ERROR_LEVEL_WARNNING");var Ht={isObfuscated:!0,browserStackInfo:ae},cd={pageUrl:window.location.href,kvPairs:[]};A("FEXP_EXPERIMENTS")&&(cd.experimentIds=A("FEXP_EXPERIMENTS"));var Ui=A("LATEST_ECATCHER_SERVICE_TRACKING_PARAMS",void 0);if(!ai()&&Ui)for(var xo=p(Object.keys(Ui)),nc=xo.next();!nc.done;nc=xo.next()){var yo=nc.value;
cd.kvPairs.push({key:yo,value:String(Ui[yo])})}var Vi=G.params;if(Vi){var zo=p(Object.keys(Vi));for(nc=zo.next();!nc.done;nc=zo.next()){var Ao=nc.value;cd.kvPairs.push({key:"client."+Ao,value:String(Vi[Ao])})}}var Bo=$h("SERVER_NAME"),Co=$h("SERVER_VERSION");Bo&&Co&&(cd.kvPairs.push({key:"server.name",value:Bo}),cd.kvPairs.push({key:"server.version",value:Co}));wo={errorMetadata:cd,stackTrace:Ht,logMessage:Ti}}var Do=wo;if(!Do)break a;ok("clientError",Do)}("ERROR"===$d||M("errors_flush_gel_always_killswitch"))&&
$o(void 0,void 0,!1)}if(!M("suppress_error_204_logging")){var be=G.params||{},Nb={urlParams:{a:"logerror",t:"jserror",type:G.name,msg:G.message.substr(0,250),line:G.lineNumber,level:h,"client.name":be.name},postParams:{url:A("PAGE_NAME",window.location.href),file:G.fileName},method:"POST"};be.version&&(Nb["client.version"]=be.version);if(Nb.postParams){G.stack&&(Nb.postParams.stack=G.stack);for(var Eo=p(Object.keys(be)),Wi=Eo.next();!Wi.done;Wi=Eo.next()){var Fo=Wi.value;Nb.postParams["client."+Fo]=
be[Fo]}var Xi=A("LATEST_ECATCHER_SERVICE_TRACKING_PARAMS",void 0);if(Xi)for(var Go=p(Object.keys(Xi)),Yi=Go.next();!Yi.done;Yi=Go.next()){var Ho=Yi.value;Nb.postParams[Ho]=Xi[Ho]}var Io=A("SERVER_NAME",void 0),Jo=A("SERVER_VERSION",void 0);Io&&Jo&&(Nb.postParams["server.name"]=Io,Nb.postParams["server.version"]=Jo)}dj(A("ECATCHER_REPORT_HOST","")+"/error_204",Nb)}try{Mp.add(G.message)}catch(fv){}Np++}}}}
function Up(){for(var a=p(Rp),b=a.next();!b.done;b=a.next())if(fk(b.value.toLowerCase()))return!0;return!1}
function Vp(a){var b=Ja.apply(1,arguments),c=a;c.args||(c.args=[]);c.args.push.apply(c.args,fa(b))}
;function Wp(){this.register=new Map}
function Xp(a){a=p(a.register.values());for(var b=a.next();!b.done;b=a.next())b.value.Wo("ABORTED")}
Wp.prototype.clear=function(){Xp(this);this.register.clear()};
var Yp=new Wp;var Zp=Date.now().toString();
function $p(){a:{if(window.crypto&&window.crypto.getRandomValues)try{var a=Array(16),b=new Uint8Array(16);window.crypto.getRandomValues(b);for(var c=0;c<a.length;c++)a[c]=b[c];var d=a;break a}catch(e){}d=Array(16);for(a=0;16>a;a++){b=Date.now();for(c=0;c<b%23;c++)d[a]=Math.random();d[a]=Math.floor(256*Math.random())}if(Zp)for(a=1,b=0;b<Zp.length;b++)d[a%16]=d[a%16]^d[(a-1)%16]/4^Zp.charCodeAt(b),a++}a=[];for(b=0;b<d.length;b++)a.push("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_".charAt(d[b]&63));
return a.join("")}
;var aq=x.ytLoggingDocDocumentNonce_;aq||(aq=$p(),Za("ytLoggingDocDocumentNonce_",aq));var bq=aq;var cq={Bg:0,rd:1,Bd:2,fk:3,Dg:4,lo:5,Vk:6,wm:7,Yl:8,0:"DEFAULT",1:"CHAT",2:"CONVERSATIONS",3:"MINIPLAYER",4:"DIALOG",5:"VOZ",6:"MUSIC_WATCH_TABS",7:"SHARE",8:"PUSH_NOTIFICATIONS"};function dq(a){this.h=a}
function eq(a){return new dq({trackingParams:a})}
dq.prototype.getAsJson=function(){var a={};void 0!==this.h.trackingParams?a.trackingParams=this.h.trackingParams:(a.veType=this.h.veType,void 0!==this.h.veCounter&&(a.veCounter=this.h.veCounter),void 0!==this.h.elementIndex&&(a.elementIndex=this.h.elementIndex));void 0!==this.h.dataElement&&(a.dataElement=this.h.dataElement.getAsJson());void 0!==this.h.youtubeData&&(a.youtubeData=this.h.youtubeData);return a};
dq.prototype.getAsJspb=function(){var a=new hh;void 0!==this.h.trackingParams?D(a,1,this.h.trackingParams):(void 0!==this.h.veType&&D(a,2,this.h.veType),void 0!==this.h.veCounter&&D(a,6,this.h.veCounter),void 0!==this.h.elementIndex&&D(a,3,this.h.elementIndex));if(void 0!==this.h.dataElement){var b=this.h.dataElement.getAsJspb();I(a,7,b)}void 0!==this.h.youtubeData&&I(a,8,this.h.jspbYoutubeData);return a};
dq.prototype.toString=function(){return JSON.stringify(this.getAsJson())};
dq.prototype.isClientVe=function(){return!this.h.trackingParams&&!!this.h.veType};function fq(a){a=void 0===a?0:a;return 0===a?"client-screen-nonce":"client-screen-nonce."+a}
function gq(a){a=void 0===a?0:a;return 0===a?"ROOT_VE_TYPE":"ROOT_VE_TYPE."+a}
function hq(a){return A(gq(void 0===a?0:a),void 0)}
y("yt_logging_screen.getRootVeType",hq,void 0);function iq(a){return(a=hq(void 0===a?0:a))?new dq({veType:a,youtubeData:void 0,jspbYoutubeData:void 0}):null}
function jq(){var a=A("csn-to-ctt-auth-info");a||(a={},Zh("csn-to-ctt-auth-info",a));return a}
function kq(a){a=A(fq(void 0===a?0:a));if(!a&&!A("USE_CSN_FALLBACK",!0))return null;a||(a="UNDEFINED_CSN");return a?a:null}
y("yt_logging_screen.getCurrentCsn",kq,void 0);function lq(a,b,c){var d=jq();(c=kq(c))&&delete d[c];b&&(d[a]=b)}
function mq(a){return jq()[a]}
y("yt_logging_screen.getCttAuthInfo",mq,void 0);
function nq(a,b,c,d){c=void 0===c?0:c;if(a!==A(fq(c))||b!==A(gq(c)))lq(a,d,c),Zh(fq(c),a),Zh(gq(c),b),b=function(){setTimeout(function(){if(a)if(M("web_time_via_jspb")){var e=new ih;D(e,1,bq);D(e,2,a);M("use_default_heartbeat_client")?Lp(e):Lp(e,void 0,tn)}else e={clientDocumentNonce:bq,clientScreenNonce:a},M("use_default_heartbeat_client")?ok("foregroundHeartbeatScreenAssociated",e):op("foregroundHeartbeatScreenAssociated",e,tn)},0)},"requestAnimationFrame"in window?window.requestAnimationFrame(b):
b()}
y("yt_logging_screen.setCurrentScreen",nq,void 0);var oq=window.yt&&window.yt.msgs_||window.ytcfg&&window.ytcfg.msgs||{};y("yt.msgs_",oq,void 0);function pq(a){Oh(oq,arguments)}
;var qq={qd:3611,Ec:27686,Fc:85013,Gc:23462,Ic:42016,Jc:62407,Kc:26926,Hc:43781,Lc:51236,Mc:79148,Nc:50160,Oc:77504,bd:87907,cd:18630,dd:54445,ed:80935,fd:105675,gd:37521,hd:147285,jd:47786,kd:98349,ld:123695,md:6827,nd:29434,od:7282,pd:124448,td:32276,sd:76278,ud:147868,vd:147869,wd:93911,xd:106531,yd:27259,zd:27262,Ad:27263,Cd:21759,Dd:27107,Ed:62936,Fd:49568,Gd:38408,Hd:80637,Id:68727,Jd:68728,Kd:80353,Ld:80356,Md:74610,Nd:45707,Od:83962,Pd:83970,Qd:46713,Rd:89711,Sd:74612,Td:93265,Ud:74611,Vd:131380,
Xd:128979,Yd:139311,Zd:128978,Wd:131391,ae:105350,ce:139312,de:134800,be:131392,ge:113533,he:93252,ie:99357,ke:94521,le:114252,me:113532,ne:94522,je:94583,oe:88E3,pe:139580,qe:93253,re:93254,se:94387,te:94388,ue:93255,we:97424,ee:72502,xe:110111,ye:76019,Ae:117092,Be:117093,ze:89431,Ce:110466,De:77240,Ee:60508,Fe:148123,Ge:148124,He:137401,Ie:137402,Je:137046,Ke:73393,Le:113534,Me:92098,Ne:131381,Oe:84517,Pe:83759,Qe:80357,Re:86113,Se:72598,Te:72733,Ue:107349,Ve:124275,We:118203,Xe:133275,Ye:133274,
Ze:133272,af:133273,bf:133276,cf:144507,df:143247,ef:143248,ff:143249,gf:143250,hf:143251,jf:144401,lf:117431,kf:133797,mf:128572,nf:133405,pf:117429,qf:117430,rf:117432,sf:120080,tf:117259,uf:121692,vf:145656,wf:145655,xf:145653,yf:145654,zf:145657,Af:132972,Bf:133051,Cf:133658,Df:132971,Ef:97615,Gf:143359,Ff:143356,If:143361,Hf:143358,Kf:143360,Jf:143357,Lf:142303,Mf:143353,Nf:143354,Of:144479,Pf:143355,Qf:31402,Sf:133624,Tf:146477,Uf:133623,Vf:133622,Rf:133621,Wf:84774,Xf:95117,Yf:98930,Zf:98931,
ag:98932,cg:43347,dg:129889,eg:45474,fg:100352,gg:84758,hg:98443,ig:117985,jg:74613,kg:74614,lg:64502,mg:136032,ng:74615,og:74616,pg:122224,qg:74617,rg:77820,sg:74618,tg:93278,ug:93274,vg:93275,wg:93276,xg:22110,yg:29433,zg:133798,Ag:132295,Cg:120541,Eg:82047,Fg:113550,Gg:75836,Hg:75837,Ig:42352,Jg:84512,Kg:76065,Lg:75989,Mg:16623,Ng:32594,Og:27240,Pg:32633,Qg:74858,Sg:3945,Rg:16989,Tg:45520,Ug:25488,Vg:25492,Wg:25494,Xg:55760,Yg:14057,Zg:18451,ah:57204,bh:57203,dh:17897,eh:57205,fh:18198,gh:17898,
hh:17909,ih:43980,jh:46220,kh:11721,lh:147994,mh:49954,nh:96369,oh:3854,ph:56251,qh:25624,Hh:16906,Ih:99999,Jh:68172,Kh:27068,Lh:47973,Mh:72773,Nh:26970,Oh:26971,Ph:96805,Qh:17752,Rh:73233,Sh:109512,Th:22256,Uh:14115,Vh:22696,Wh:89278,Xh:89277,Yh:109513,Zh:43278,ai:43459,bi:43464,ci:89279,di:43717,fi:55764,gi:22255,hi:147912,ii:89281,ji:40963,ki:43277,li:43442,mi:91824,ni:120137,oi:96367,ri:36850,si:72694,ti:37414,vi:36851,xi:124863,wi:121343,yi:73491,zi:54473,Ai:43375,Bi:46674,Ci:143815,Di:139095,
Ei:144402,Fi:32473,Gi:72901,Hi:72906,Ii:50947,Ji:50612,Ki:50613,Li:50942,Mi:84938,Ni:84943,Oi:84939,Pi:84941,Qi:84944,Ri:84940,Si:84942,Ti:35585,Ui:51926,Vi:79983,Wi:63238,Xi:18921,Yi:63241,Zi:57893,aj:41182,bj:135732,cj:33424,dj:22207,ej:42993,fj:36229,gj:22206,hj:22205,ij:18993,jj:19001,kj:18990,lj:18991,mj:18997,nj:18725,oj:19003,pj:36874,qj:44763,rj:33427,sj:67793,tj:22182,uj:37091,vj:34650,wj:50617,xj:47261,yj:22287,zj:25144,Aj:97917,Bj:62397,Cj:125598,Dj:137935,Ej:36961,Fj:108035,Gj:27426,Hj:27857,
Ij:27846,Jj:27854,Kj:69692,Lj:61411,Mj:39299,Nj:38696,Oj:62520,Pj:36382,Qj:108701,Rj:50663,Sj:36387,Tj:14908,Uj:37533,Vj:105443,Wj:61635,Xj:62274,Yj:133818,Zj:65702,ak:65703,bk:65701,ck:76256,dk:37671,ek:49953,gk:36216,hk:28237,ik:39553,jk:29222,kk:26107,lk:38050,mk:26108,pk:120745,nk:26109,qk:26110,rk:66881,sk:28236,tk:14586,uk:57929,vk:74723,wk:44098,xk:44099,Ak:23528,Bk:61699,yk:134104,zk:134103,Ck:59149,Dk:101951,Ek:97346,Fk:118051,Gk:95102,Hk:64882,Ik:119505,Jk:63595,Kk:63349,Lk:95101,Mk:75240,
Nk:27039,Ok:68823,Pk:21537,Qk:83464,Rk:75707,Sk:83113,Tk:101952,Uk:101953,Wk:79610,Xk:125755,Yk:24402,Zk:24400,al:32925,bl:57173,dl:122502,fl:145268,il:138480,jl:64423,kl:64424,ll:33986,ml:100828,nl:129089,ol:21409,sl:135155,ul:135156,vl:135157,wl:135158,xl:135159,yl:135160,zl:135161,Al:135162,Bl:135163,Cl:135164,Dl:135165,El:135166,pl:11070,ql:11074,rl:17880,Fl:14001,Hl:30709,Il:30707,Jl:30711,Kl:30710,Ll:30708,Gl:26984,Ml:146143,Nl:63648,Ol:63649,Pl:51879,Ql:111059,Rl:5754,Sl:20445,Ul:130975,Tl:130976,
Vl:110386,Wl:113746,Xl:66557,Zl:17310,am:28631,bm:21589,cm:68012,dm:60480,em:138664,fm:141121,gm:31571,hm:141978,im:76980,jm:41577,km:45469,lm:38669,mm:13768,nm:13777,om:141842,pm:62985,qm:4724,rm:59369,sm:43927,tm:43928,um:12924,vm:100355,ym:56219,zm:27669,Am:10337,xm:47896,Bm:122629,Dm:139723,Cm:139722,Em:121258,Fm:107598,Gm:127991,Hm:96639,Im:107536,Jm:130169,Km:96661,Lm:145188,Mm:96658,Nm:116646,Om:121122,Pm:96660,Qm:127738,Rm:127083,Sm:147842,Tm:104443,Um:96659,Vm:147595,Wm:106442,Xm:134840,
Ym:63667,Zm:63668,an:63669,bn:130686,cn:147036,dn:78314,en:147799,fn:55761,gn:127098,hn:134841,jn:96368,kn:67374,ln:48992,mn:146176,nn:49956,pn:31961,qn:26388,rn:23811,sn:5E4,tn:126250,un:96370,vn:47355,wn:47356,xn:37935,yn:45521,zn:21760,An:83769,Bn:49977,Cn:49974,Dn:93497,En:93498,Fn:34325,Gn:140759,Hn:115803,In:123707,Jn:100081,Kn:35309,Ln:68314,Mn:25602,Nn:100339,On:143516,Pn:59018,Qn:18248,Rn:50625,Sn:9729,Tn:37168,Un:37169,Vn:21667,Wn:16749,Xn:18635,Yn:39305,Zn:18046,ao:53969,bo:8213,co:93926,
eo:102852,fo:110099,ho:22678,jo:69076,ko:137575,mo:139224,no:100856,oo:17736,po:3832,qo:147111,ro:55759,so:64031,yo:93044,zo:93045,Ao:34388,Bo:17657,Co:17655,Do:39579,Eo:39578,Fo:77448,Go:8196,Ho:11357,Io:69877,Jo:8197,Ko:82039};function rq(){var a=wb(sq),b;return fg(new Zf(function(c,d){a.onSuccess=function(e){Bi(e)?c(new tq(e)):d(new uq("Request failed, status="+(e&&"status"in e?e.status:-1),"net.badstatus",e))};
a.onError=function(e){d(new uq("Unknown request error","net.unknown",e))};
a.onTimeout=function(e){d(new uq("Request timed out","net.timeout",e))};
b=dj("//googleads.g.doubleclick.net/pagead/id",a)}),function(c){c instanceof gg&&b.abort();
return dg(c)})}
function uq(a,b,c){bb.call(this,a+", errorCode="+b);this.errorCode=b;this.xhr=c;this.name="PromiseAjaxError"}
r(uq,bb);function tq(a){this.xhr=a}
;function vq(){this.i=0;this.h=null}
vq.prototype.then=function(a,b,c){return 1===this.i&&a?(a=a.call(c,this.h),Yf(a)?a:wq(a)):2===this.i&&b?(a=b.call(c,this.h),Yf(a)?a:xq(a)):this};
vq.prototype.getValue=function(){return this.h};
vq.prototype.$goog_Thenable=!0;function xq(a){var b=new vq;a=void 0===a?null:a;b.i=2;b.h=void 0===a?null:a;return b}
function wq(a){var b=new vq;a=void 0===a?null:a;b.i=1;b.h=void 0===a?null:a;return b}
;function yq(){if(le()||ek&&fk("applewebkit")&&!fk("version")&&(!fk("safari")||fk("gsa/"))||xc&&fk("version/"))return!0;if(M("enable_web_eom_visitor_data"))return A("EOM_VISITOR_DATA",void 0)?!1:!0;var a=A("INNERTUBE_CLIENT_NAME");return!a||"WEB"!==a&&"MWEB"!==a?!0:(a=pj("CONSENT"))?a.startsWith("YES+"):!0}
;function zq(a){bb.call(this,a.message||a.description||a.name);this.isMissing=a instanceof Aq;this.isTimeout=a instanceof uq&&"net.timeout"==a.errorCode;this.isCanceled=a instanceof gg}
r(zq,bb);zq.prototype.name="BiscottiError";function Aq(){bb.call(this,"Biscotti ID is missing from server")}
r(Aq,bb);Aq.prototype.name="BiscottiMissingError";var sq={format:"RAW",method:"GET",timeout:5E3,withCredentials:!0},Bq=null;function li(){if(M("disable_biscotti_fetch_entirely_for_all_web_clients"))return dg(Error("Biscotti id fetching has been disabled entirely."));if(!yq())return dg(Error("User has not consented - not fetching biscotti id."));if("1"==ub())return dg(Error("Biscotti ID is not available in private embed mode"));Bq||(Bq=fg(rq().then(Cq),function(a){return Dq(2,a)}));
return Bq}
function Cq(a){a=a.xhr.responseText;if(0!=a.lastIndexOf(")]}'",0))throw new Aq;a=JSON.parse(a.substr(4));if(1<(a.type||1))throw new Aq;a=a.id;mi(a);Bq=wq(a);Eq(18E5,2);return a}
function Dq(a,b){b=new zq(b);mi("");Bq=xq(b);0<a&&Eq(12E4,a-1);throw b;}
function Eq(a,b){Ci(function(){fg(rq().then(Cq,function(c){return Dq(b,c)}),db)},a)}
function Fq(){try{var a=z("yt.ads.biscotti.getId_");return a?a():li()}catch(b){return dg(b)}}
;function Gq(a){if("1"!=ub()){a&&ki();try{Fq().then(function(){},function(){}),Ci(Gq,18E5)}catch(b){ii(b)}}}
;function Hq(){this.zc=!0}
function Iq(a){var b={},c=ne([]);c&&(b.Authorization=c,c=a=null==a?void 0:a.sessionIndex,void 0===c&&(c=Number(A("SESSION_INDEX",0)),c=isNaN(c)?0:c),M("voice_search_auth_header_removal")||(b["X-Goog-AuthUser"]=c),"INNERTUBE_HOST_OVERRIDE"in Sh||(b["X-Origin"]=window.location.origin),void 0===a&&"DELEGATED_SESSION_ID"in Sh&&(b["X-Goog-PageId"]=A("DELEGATED_SESSION_ID")));return b}
;var Jq=Symbol("injectionDeps");function Kq(a){this.name=a}
Kq.prototype.toString=function(){return"InjectionToken("+this.name+")"};
function Lq(){this.key=Mq}
function Nq(){this.providers=new Map;this.h=new Map}
Nq.prototype.resolve=function(a){return a instanceof Lq?Oq(this,a.key,[],!0):Oq(this,a,[])};
function Oq(a,b,c,d){d=void 0===d?!1:d;if(-1<c.indexOf(b))throw Error("Deps cycle for: "+b);if(a.h.has(b))return a.h.get(b);if(!a.providers.has(b)){if(d)return;throw Error("No provider for: "+b);}d=a.providers.get(b);c.push(b);if(d.Dc)var e=d.Dc;else if(d.Cc)e=d[Jq]?Pq(a,d[Jq],c):[],e=d.Cc.apply(d,fa(e));else if(d.Kb){e=d.Kb;var f=e[Jq]?Pq(a,e[Jq],c):[];e=new (Function.prototype.bind.apply(e,[null].concat(fa(f))))}else throw Error("Could not resolve providers for: "+b);c.pop();d.ap||a.h.set(b,e);
return e}
function Pq(a,b,c){return b?b.map(function(d){return d instanceof Lq?Oq(a,d.key,c,!0):Oq(a,d,c)}):[]}
;var Qq;var Rq={identityType:"UNAUTHENTICATED_IDENTITY_TYPE_UNKNOWN"};var Sq=new Map([["dark","USER_INTERFACE_THEME_DARK"],["light","USER_INTERFACE_THEME_LIGHT"]]);function Tq(){var a=void 0===a?window.location.href:a;if(M("kevlar_disable_theme_param"))return null;cc(dc(5,a));try{var b=ui(a).theme;return Sq.get(b)||null}catch(c){}return null}
;function Uq(){this.h={};if(this.i=qj()){var a=pj("CONSISTENCY");a&&Vq(this,{encryptedTokenJarContents:a})}}
Uq.prototype.handleResponse=function(a,b){var c,d;b=(null==(c=b.ba.context)?void 0:null==(d=c.request)?void 0:d.consistencyTokenJars)||[];var e;(a=null==(e=a.responseContext)?void 0:e.consistencyTokenJar)&&this.replace(b,a)};
Uq.prototype.replace=function(a,b){a=p(a);for(var c=a.next();!c.done;c=a.next())delete this.h[c.value.encryptedTokenJarContents];Vq(this,b)};
function Vq(a,b){if(b.encryptedTokenJarContents&&(a.h[b.encryptedTokenJarContents]=b,"string"===typeof b.expirationSeconds)){var c=Number(b.expirationSeconds);setTimeout(function(){delete a.h[b.encryptedTokenJarContents]},1E3*c);
a.i&&oj("CONSISTENCY",b.encryptedTokenJarContents,c,void 0,!0)}}
;var Wq=window.location.hostname.split(".").slice(-2).join(".");function Xq(){var a=A("LOCATION_PLAYABILITY_TOKEN");"TVHTML5"===A("INNERTUBE_CLIENT_NAME")&&(this.h=Yq(this))&&(a=this.h.get("yt-location-playability-token"));a&&(this.locationPlayabilityToken=a,this.i=void 0)}
var Zq;Xq.getInstance=function(){Zq=z("yt.clientLocationService.instance");Zq||(Zq=new Xq,y("yt.clientLocationService.instance",Zq,void 0));return Zq};
Xq.prototype.setLocationOnInnerTubeContext=function(a){a.client||(a.client={});this.i?(a.client.locationInfo||(a.client.locationInfo={}),a.client.locationInfo.latitudeE7=1E7*this.i.coords.latitude,a.client.locationInfo.longitudeE7=1E7*this.i.coords.longitude,a.client.locationInfo.horizontalAccuracyMeters=Math.round(this.i.coords.accuracy),a.client.locationInfo.forceLocationPlayabilityTokenRefresh=!0):this.locationPlayabilityToken&&(a.client.locationPlayabilityToken=this.locationPlayabilityToken)};
Xq.prototype.handleResponse=function(a){var b;a=null==(b=a.responseContext)?void 0:b.locationPlayabilityToken;void 0!==a&&(this.locationPlayabilityToken=a,this.i=void 0,"TVHTML5"===A("INNERTUBE_CLIENT_NAME")?(this.h=Yq(this))&&this.h.set("yt-location-playability-token",a,15552E3):oj("YT_CL",JSON.stringify({loctok:a}),15552E3,Wq,!0))};
function Yq(a){return void 0===a.h?new Pj("yt-client-location"):a.h}
Xq.prototype.getCurrentPositionFromGeolocation=function(){var a=this;if(!(navigator&&navigator.geolocation&&navigator.geolocation.getCurrentPosition)||!M("web_enable_browser_geolocation_api")&&!M("enable_handoff_location_2fa_on_mweb"))return Promise.reject(Error("Geolocation unsupported"));var b=!1,c=1E4;M("enable_handoff_location_2fa_on_mweb")&&(b=!0,c=15E3);return new Promise(function(d,e){navigator.geolocation.getCurrentPosition(function(f){a.i=f;d(f)},function(f){e(f)},{enableHighAccuracy:b,
maximumAge:0,timeout:c})})};
Xq.prototype.createUnpluggedLocationInfo=function(a){var b={};a=a.coords;if(null==a?0:a.latitude)b.latitudeE7=Math.floor(1E7*a.latitude);if(null==a?0:a.longitude)b.longitudeE7=Math.floor(1E7*a.longitude);if(null==a?0:a.accuracy)b.locationRadiusMeters=Math.round(a.accuracy);return b};function $q(a,b){var c;if((null==(c=a.signalServiceEndpoint)?0:c.signal)&&b.za&&(c=b.za[a.signalServiceEndpoint.signal]))return c();var d;if((null==(d=a.continuationCommand)?0:d.request)&&b.Rb&&(d=b.Rb[a.continuationCommand.request]))return d();for(var e in a)if(b.ob[e]&&(a=b.ob[e]))return a()}
;function ar(a){return function(){return new a}}
;var br={},cr=(br.WEB_UNPLUGGED="^unplugged/",br.WEB_UNPLUGGED_ONBOARDING="^unplugged/",br.WEB_UNPLUGGED_OPS="^unplugged/",br.WEB_UNPLUGGED_PUBLIC="^unplugged/",br.WEB_CREATOR="^creator/",br.WEB_KIDS="^kids/",br.WEB_EXPERIMENTS="^experiments/",br.WEB_MUSIC="^music/",br.WEB_REMIX="^music/",br.WEB_MUSIC_EMBEDDED_PLAYER="^music/",br.WEB_MUSIC_EMBEDDED_PLAYER="^main_app/|^sfv/",br);
function dr(a){var b=void 0===b?"UNKNOWN_INTERFACE":b;if(1===a.length)return a[0];var c=cr[b];if(c){var d=new RegExp(c),e=p(a);for(c=e.next();!c.done;c=e.next())if(c=c.value,d.exec(c))return c}var f=[];Object.entries(cr).forEach(function(g){var h=p(g);g=h.next().value;h=h.next().value;b!==g&&f.push(h)});
d=new RegExp(f.join("|"));a.sort(function(g,h){return g.length-h.length});
e=p(a);for(c=e.next();!c.done;c=e.next())if(c=c.value,!d.exec(c))return c;return a[0]}
;function er(a,b){return{method:void 0===b?"POST":b,mode:wi(a)?"same-origin":"cors",credentials:wi(a)?"same-origin":"include"}}
;function fr(){}
fr.prototype.o=function(a,b,c){b=void 0===b?{}:b;c=void 0===c?Rq:c;var d=a.clickTrackingParams,e=this.l,f=!1;f=void 0===f?!1:f;e=void 0===e?!1:e;var g=A("INNERTUBE_CONTEXT");if(g){g=xb(g);M("web_no_tracking_params_in_shell_killswitch")||delete g.clickTracking;g.client||(g.client={});var h=g.client;"MWEB"===h.clientName&&(h.clientFormFactor=A("IS_TABLET")?"LARGE_FORM_FACTOR":"SMALL_FORM_FACTOR");h.screenWidthPoints=window.innerWidth;h.screenHeightPoints=window.innerHeight;h.screenPixelDensity=Math.round(window.devicePixelRatio||
1);h.screenDensityFloat=window.devicePixelRatio||1;h.utcOffsetMinutes=-Math.floor((new Date).getTimezoneOffset());var k=void 0===k?!1:k;sj.getInstance();var m="USER_INTERFACE_THEME_LIGHT";vj(165)?m="USER_INTERFACE_THEME_DARK":vj(174)?m="USER_INTERFACE_THEME_LIGHT":!M("kevlar_legacy_browsers")&&window.matchMedia&&window.matchMedia("(prefers-color-scheme)").matches&&window.matchMedia("(prefers-color-scheme: dark)").matches&&(m="USER_INTERFACE_THEME_DARK");k=k?m:Tq()||m;h.userInterfaceTheme=k;if(!f){if(k=
Cj())h.connectionType=k;M("web_log_effective_connection_type")&&(k=Dj())&&(g.client.effectiveConnectionType=k)}var q;if(M("web_log_memory_total_kbytes")&&(null==(q=x.navigator)?0:q.deviceMemory)){var u;q=null==(u=x.navigator)?void 0:u.deviceMemory;g.client.memoryTotalKbytes=""+1E6*q}u=ui(x.location.href);!M("web_populate_internal_geo_killswitch")&&u.internalcountrycode&&(h.internalGeo=u.internalcountrycode);"MWEB"===h.clientName||"WEB"===h.clientName?(h.mainAppWebInfo={graftUrl:x.location.href},M("kevlar_woffle")&&
lj.h&&(h.mainAppWebInfo.pwaInstallabilityStatus=lj.h.h?"PWA_INSTALLABILITY_STATUS_CAN_BE_INSTALLED":"PWA_INSTALLABILITY_STATUS_UNKNOWN"),h.mainAppWebInfo.webDisplayMode=mj(),h.mainAppWebInfo.isWebNativeShareAvailable=navigator&&void 0!==navigator.share):"TVHTML5"===h.clientName&&(!M("web_lr_app_quality_killswitch")&&(u=A("LIVING_ROOM_APP_QUALITY"))&&(h.tvAppInfo=Object.assign(h.tvAppInfo||{},{appQuality:u})),u=A("LIVING_ROOM_CERTIFICATION_SCOPE"))&&(h.tvAppInfo=Object.assign(h.tvAppInfo||{},{certificationScope:u}));
if(!M("web_populate_time_zone_itc_killswitch")){b:{if("undefined"!==typeof Intl)try{var C=(new Intl.DateTimeFormat).resolvedOptions().timeZone;break b}catch(Oa){}C=void 0}C&&(h.timeZone=C)}(C=di())?h.experimentsToken=C:delete h.experimentsToken;C=ei();Uq.h||(Uq.h=new Uq);h=Uq.h.h;u=[];q=0;for(var v in h)u[q++]=h[v];g.request=Object.assign({},g.request,{internalExperimentFlags:C,consistencyTokenJars:u});!M("web_prequest_context_killswitch")&&(v=A("INNERTUBE_CONTEXT_PREQUEST_CONTEXT"))&&(g.request.externalPrequestContext=
v);C=sj.getInstance();v=vj(58);C=C.get("gsml","");g.user=Object.assign({},g.user);v&&(g.user.enableSafetyMode=v);C&&(g.user.lockedSafetyMode=!0);M("warm_op_csn_cleanup")?e&&(f=kq())&&(g.clientScreenNonce=f):!f&&(f=kq())&&(g.clientScreenNonce=f);d&&(g.clickTracking={clickTrackingParams:d});if(d=z("yt.mdx.remote.remoteClient_"))g.remoteClient=d;M("web_enable_client_location_service")&&Xq.getInstance().setLocationOnInnerTubeContext(g);try{var E=xi(void 0),F=E.bid;delete E.bid;g.adSignalsInfo={params:[],
bid:F};var H=p(Object.entries(E));for(var R=H.next();!R.done;R=H.next()){var O=p(R.value),S=O.next().value,ka=O.next().value;E=S;F=ka;d=void 0;null==(d=g.adSignalsInfo.params)||d.push({key:E,value:""+F})}}catch(Oa){Sp(Oa)}H=g}else Sp(Error("Error: No InnerTubeContext shell provided in ytconfig.")),H={};H={context:H};if(R=this.h(a)){this.i(H,R,b);var N;b="/youtubei/v1/"+dr(this.j());var Ba;(a=null==(N=a.commandMetadata)?void 0:null==(Ba=N.webCommandMetadata)?void 0:Ba.apiUrl)&&(b=a);N=b;(Ba=A("INNERTUBE_HOST_OVERRIDE"))&&
(N=String(Ba)+String(fc(N)));Ba={};Ba.key=A("INNERTUBE_API_KEY");M("json_condensed_response")&&(Ba.prettyPrint="false");N=vi(N,Ba||{},!1);N={input:N,ra:er(N),ba:H,config:Object.assign({},void 0)};N.config.Ga?N.config.Ga.identity=c:N.config.Ga={identity:c};return N}Sp(new Q("Error: Failed to create Request from Command.",a))};
da.Object.defineProperties(fr.prototype,{l:{configurable:!0,enumerable:!0,get:function(){return!1}}});function gr(){}
r(gr,fr);gr.prototype.o=function(){return{input:"/getDatasyncIdsEndpoint",ra:er("/getDatasyncIdsEndpoint","GET"),ba:{}}};
gr.prototype.j=function(){return[]};
gr.prototype.h=function(){};
gr.prototype.i=function(){};var hr={},ir=(hr.GET_DATASYNC_IDS=ar(gr),hr);function jr(a){var b=Ja.apply(1,arguments);if(!kr(a)||b.some(function(e){return!kr(e)}))throw Error("Only objects may be merged.");
var c=a;b=p(b);for(var d=b.next();!d.done;d=b.next())lr(c,d.value);return c}
function lr(a,b){for(var c in b)if(kr(b[c])){if(c in a&&!kr(a[c]))throw Error("Cannot merge an object into a non-object.");c in a||(a[c]={});lr(a[c],b[c])}else if(mr(b[c])){if(c in a&&!mr(a[c]))throw Error("Cannot merge an array into a non-array.");c in a||(a[c]=[]);nr(a[c],b[c])}else a[c]=b[c];return a}
function nr(a,b){b=p(b);for(var c=b.next();!c.done;c=b.next())c=c.value,kr(c)?a.push(lr({},c)):mr(c)?a.push(nr([],c)):a.push(c);return a}
function kr(a){return"object"===typeof a&&!Array.isArray(a)}
function mr(a){return"object"===typeof a&&Array.isArray(a)}
;function or(a,b){Vl.call(this,1,arguments);this.timer=b}
r(or,Vl);var pr=new Wl("aft-recorded",or);var qr=window;function rr(){this.timing={};this.clearResourceTimings=function(){};
this.webkitClearResourceTimings=function(){};
this.mozClearResourceTimings=function(){};
this.msClearResourceTimings=function(){};
this.oClearResourceTimings=function(){}}
var T=qr.performance||qr.mozPerformance||qr.msPerformance||qr.webkitPerformance||new rr;var sr=!1,tr={'script[name="scheduler/scheduler"]':"sj",'script[name="player/base"]':"pj",'link[rel="stylesheet"][name="www-player"]':"pc",'link[rel="stylesheet"][name="player/www-player"]':"pc",'script[name="desktop_polymer/desktop_polymer"]':"dpj",'link[rel="import"][name="desktop_polymer"]':"dph",'script[name="mobile-c3"]':"mcj",'link[rel="stylesheet"][name="mobile-c3"]':"mcc",'script[name="player-plasma-ias-phone/base"]':"mcppj",'script[name="player-plasma-ias-tablet/base"]':"mcptj",'link[rel="stylesheet"][name="mobile-polymer-player-ias"]':"mcpc",
'link[rel="stylesheet"][name="mobile-polymer-player-svg-ias"]':"mcpsc",'script[name="mobile_blazer_core_mod"]':"mbcj",'link[rel="stylesheet"][name="mobile_blazer_css"]':"mbc",'script[name="mobile_blazer_logged_in_users_mod"]':"mbliuj",'script[name="mobile_blazer_logged_out_users_mod"]':"mblouj",'script[name="mobile_blazer_noncore_mod"]':"mbnj","#player_css":"mbpc",'script[name="mobile_blazer_desktopplayer_mod"]':"mbpj",'link[rel="stylesheet"][name="mobile_blazer_tablet_css"]':"mbtc",'script[name="mobile_blazer_watch_mod"]':"mbwj"};
Xa(T.clearResourceTimings||T.webkitClearResourceTimings||T.mozClearResourceTimings||T.msClearResourceTimings||T.oClearResourceTimings||db,T);function ur(a){var b=vr(a);if(b.aft)return b.aft;a=A((a||"")+"TIMING_AFT_KEYS",["ol"]);for(var c=a.length,d=0;d<c;d++){var e=b[a[d]];if(e)return e}return NaN}
function wr(){var a;if(M("csi_use_performance_navigation_timing")){var b,c,d,e=null==T?void 0:null==(a=T.getEntriesByType)?void 0:null==(b=a.call(T,"navigation"))?void 0:null==(c=b[0])?void 0:null==(d=c.toJSON)?void 0:d.call(c);e?(e.requestStart=xr(e.requestStart),e.responseEnd=xr(e.responseEnd),e.redirectStart=xr(e.redirectStart),e.redirectEnd=xr(e.redirectEnd),e.domainLookupEnd=xr(e.domainLookupEnd),e.connectStart=xr(e.connectStart),e.connectEnd=xr(e.connectEnd),e.responseStart=xr(e.responseStart),
e.secureConnectionStart=xr(e.secureConnectionStart),e.domainLookupStart=xr(e.domainLookupStart),e.isPerformanceNavigationTiming=!0,a=e):a=T.timing}else a=T.timing;return a}
function yr(){return M("csi_use_time_origin")&&T.timeOrigin?Math.floor(T.timeOrigin):T.timing.navigationStart}
function xr(a){return Math.round(yr()+a)}
function zr(a){var b;(b=z("ytcsi."+(a||"")+"data_"))||(b={tick:{},info:{}},Za("ytcsi."+(a||"")+"data_",b));return b}
function Ar(a){a=zr(a);a.info||(a.info={});return a.info}
function vr(a){a=zr(a);a.tick||(a.tick={});return a.tick}
function Br(a){a=zr(a);if(a.gel){var b=a.gel;b.gelInfos||(b.gelInfos={});b.gelTicks||(b.gelTicks={})}else a.gel={gelTicks:{},gelInfos:{}};return a.gel}
function Cr(a){a=Br(a);a.gelInfos||(a.gelInfos={});return a.gelInfos}
function Dr(a){var b=zr(a).nonce;b||(b=$p(),zr(a).nonce=b);return b}
function Er(a){var b=vr(a||""),c=ur(a);c&&!sr&&(am(pr,new or(Math.round(c-b._start),a)),sr=!0)}
function Fr(a,b){for(var c=p(Object.keys(b)),d=c.next();!d.done;d=c.next())if(d=d.value,!Object.keys(a).includes(d)||"object"===typeof b[d]&&!Fr(a[d],b[d]))return!1;return!0}
;function Gr(){if(T.getEntriesByType){var a=T.getEntriesByType("paint");if(a=kb(a,function(b){return"first-paint"===b.name}))return xr(a.startTime)}a=T.timing;
return a.dc?Math.max(0,a.dc):0}
;function Hr(){var a=z("ytcsi.debug");a||(a=[],y("ytcsi.debug",a,void 0),y("ytcsi.reference",{},void 0));return a}
function Ir(a){a=a||"";var b=z("ytcsi.reference");b||(Hr(),b=z("ytcsi.reference"));if(b[a])return b[a];var c=Hr(),d={timerName:a,info:{},tick:{},span:{},jspbInfo:[]};c.push(d);return b[a]=d}
;var U={},Jr=(U.auto_search="LATENCY_ACTION_AUTO_SEARCH",U.ad_to_ad="LATENCY_ACTION_AD_TO_AD",U.ad_to_video="LATENCY_ACTION_AD_TO_VIDEO",U["analytics.explore"]="LATENCY_ACTION_CREATOR_ANALYTICS_EXPLORE",U.app_startup="LATENCY_ACTION_APP_STARTUP",U["artist.analytics"]="LATENCY_ACTION_CREATOR_ARTIST_ANALYTICS",U["artist.events"]="LATENCY_ACTION_CREATOR_ARTIST_CONCERTS",U["artist.presskit"]="LATENCY_ACTION_CREATOR_ARTIST_PROFILE",U.browse="LATENCY_ACTION_BROWSE",U.cast_splash="LATENCY_ACTION_CAST_SPLASH",
U.channels="LATENCY_ACTION_CHANNELS",U.creator_channel_dashboard="LATENCY_ACTION_CREATOR_CHANNEL_DASHBOARD",U["channel.analytics"]="LATENCY_ACTION_CREATOR_CHANNEL_ANALYTICS",U["channel.comments"]="LATENCY_ACTION_CREATOR_CHANNEL_COMMENTS",U["channel.content"]="LATENCY_ACTION_CREATOR_POST_LIST",U["channel.copyright"]="LATENCY_ACTION_CREATOR_CHANNEL_COPYRIGHT",U["channel.editing"]="LATENCY_ACTION_CREATOR_CHANNEL_EDITING",U["channel.monetization"]="LATENCY_ACTION_CREATOR_CHANNEL_MONETIZATION",U["channel.music"]=
"LATENCY_ACTION_CREATOR_CHANNEL_MUSIC",U["channel.playlists"]="LATENCY_ACTION_CREATOR_CHANNEL_PLAYLISTS",U["channel.translations"]="LATENCY_ACTION_CREATOR_CHANNEL_TRANSLATIONS",U["channel.videos"]="LATENCY_ACTION_CREATOR_CHANNEL_VIDEOS",U["channel.live_streaming"]="LATENCY_ACTION_CREATOR_LIVE_STREAMING",U.chips="LATENCY_ACTION_CHIPS",U["dialog.copyright_strikes"]="LATENCY_ACTION_CREATOR_DIALOG_COPYRIGHT_STRIKES",U["dialog.uploads"]="LATENCY_ACTION_CREATOR_DIALOG_UPLOADS",U.direct_playback="LATENCY_ACTION_DIRECT_PLAYBACK",
U.embed="LATENCY_ACTION_EMBED",U.entity_key_serialization_perf="LATENCY_ACTION_ENTITY_KEY_SERIALIZATION_PERF",U.entity_key_deserialization_perf="LATENCY_ACTION_ENTITY_KEY_DESERIALIZATION_PERF",U.explore="LATENCY_ACTION_EXPLORE",U.home="LATENCY_ACTION_HOME",U.library="LATENCY_ACTION_LIBRARY",U.live="LATENCY_ACTION_LIVE",U.live_pagination="LATENCY_ACTION_LIVE_PAGINATION",U.onboarding="LATENCY_ACTION_ONBOARDING",U.parent_profile_settings="LATENCY_ACTION_KIDS_PARENT_PROFILE_SETTINGS",U.parent_tools_collection=
"LATENCY_ACTION_PARENT_TOOLS_COLLECTION",U.parent_tools_dashboard="LATENCY_ACTION_PARENT_TOOLS_DASHBOARD",U.player_att="LATENCY_ACTION_PLAYER_ATTESTATION",U["post.comments"]="LATENCY_ACTION_CREATOR_POST_COMMENTS",U["post.edit"]="LATENCY_ACTION_CREATOR_POST_EDIT",U.prebuffer="LATENCY_ACTION_PREBUFFER",U.prefetch="LATENCY_ACTION_PREFETCH",U.profile_settings="LATENCY_ACTION_KIDS_PROFILE_SETTINGS",U.profile_switcher="LATENCY_ACTION_LOGIN",U.reel_watch="LATENCY_ACTION_REEL_WATCH",U.results="LATENCY_ACTION_RESULTS",
U.search_ui="LATENCY_ACTION_SEARCH_UI",U.search_suggest="LATENCY_ACTION_SUGGEST",U.search_zero_state="LATENCY_ACTION_SEARCH_ZERO_STATE",U.secret_code="LATENCY_ACTION_KIDS_SECRET_CODE",U.seek="LATENCY_ACTION_PLAYER_SEEK",U.settings="LATENCY_ACTION_SETTINGS",U.tenx="LATENCY_ACTION_TENX",U.video_to_ad="LATENCY_ACTION_VIDEO_TO_AD",U.watch="LATENCY_ACTION_WATCH",U.watch_it_again="LATENCY_ACTION_KIDS_WATCH_IT_AGAIN",U["watch,watch7"]="LATENCY_ACTION_WATCH",U["watch,watch7_html5"]="LATENCY_ACTION_WATCH",
U["watch,watch7ad"]="LATENCY_ACTION_WATCH",U["watch,watch7ad_html5"]="LATENCY_ACTION_WATCH",U.wn_comments="LATENCY_ACTION_LOAD_COMMENTS",U.ww_rqs="LATENCY_ACTION_WHO_IS_WATCHING",U["video.analytics"]="LATENCY_ACTION_CREATOR_VIDEO_ANALYTICS",U["video.comments"]="LATENCY_ACTION_CREATOR_VIDEO_COMMENTS",U["video.edit"]="LATENCY_ACTION_CREATOR_VIDEO_EDIT",U["video.editor"]="LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR",U["video.editor_async"]="LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR_ASYNC",U["video.live_settings"]=
"LATENCY_ACTION_CREATOR_VIDEO_LIVE_SETTINGS",U["video.live_streaming"]="LATENCY_ACTION_CREATOR_VIDEO_LIVE_STREAMING",U["video.monetization"]="LATENCY_ACTION_CREATOR_VIDEO_MONETIZATION",U["video.translations"]="LATENCY_ACTION_CREATOR_VIDEO_TRANSLATIONS",U.voice_assistant="LATENCY_ACTION_VOICE_ASSISTANT",U.cast_load_by_entity_to_watch="LATENCY_ACTION_CAST_LOAD_BY_ENTITY_TO_WATCH",U.networkless_performance="LATENCY_ACTION_NETWORKLESS_PERFORMANCE",U),V={},Kr=(V.ad_allowed="adTypesAllowed",V.yt_abt="adBreakType",
V.ad_cpn="adClientPlaybackNonce",V.ad_docid="adVideoId",V.yt_ad_an="adNetworks",V.ad_at="adType",V.aida="appInstallDataAgeMs",V.browse_id="browseId",V.p="httpProtocol",V.t="transportProtocol",V.cs="commandSource",V.cpn="clientPlaybackNonce",V.ccs="creatorInfo.creatorCanaryState",V.ctop="creatorInfo.topEntityType",V.csn="clientScreenNonce",V.docid="videoId",V.GetHome_rid="requestIds",V.GetSearch_rid="requestIds",V.GetPlayer_rid="requestIds",V.GetWatchNext_rid="requestIds",V.GetBrowse_rid="requestIds",
V.GetLibrary_rid="requestIds",V.is_continuation="isContinuation",V.is_nav="isNavigation",V.b_p="kabukiInfo.browseParams",V.is_prefetch="kabukiInfo.isPrefetch",V.is_secondary_nav="kabukiInfo.isSecondaryNav",V.nav_type="kabukiInfo.navigationType",V.prev_browse_id="kabukiInfo.prevBrowseId",V.query_source="kabukiInfo.querySource",V.voz_type="kabukiInfo.vozType",V.yt_lt="loadType",V.mver="creatorInfo.measurementVersion",V.yt_ad="isMonetized",V.nr="webInfo.navigationReason",V.nrsu="navigationRequestedSameUrl",
V.pnt="performanceNavigationTiming",V.prt="playbackRequiresTap",V.plt="playerInfo.playbackType",V.pis="playerInfo.playerInitializedState",V.paused="playerInfo.isPausedOnLoad",V.yt_pt="playerType",V.fmt="playerInfo.itag",V.yt_pl="watchInfo.isPlaylist",V.yt_pre="playerInfo.preloadType",V.yt_ad_pr="prerollAllowed",V.pa="previousAction",V.yt_red="isRedSubscriber",V.rce="mwebInfo.responseContentEncoding",V.rc="resourceInfo.resourceCache",V.scrh="screenHeight",V.scrw="screenWidth",V.st="serverTimeMs",V.ssdm=
"shellStartupDurationMs",V.br_trs="tvInfo.bedrockTriggerState",V.kebqat="kabukiInfo.earlyBrowseRequestInfo.abandonmentType",V.kebqa="kabukiInfo.earlyBrowseRequestInfo.adopted",V.label="tvInfo.label",V.is_mdx="tvInfo.isMdx",V.preloaded="tvInfo.isPreloaded",V.aac_type="tvInfo.authAccessCredentialType",V.upg_player_vis="playerInfo.visibilityState",V.query="unpluggedInfo.query",V.upg_chip_ids_string="unpluggedInfo.upgChipIdsString",V.yt_vst="videoStreamType",V.vph="viewportHeight",V.vpw="viewportWidth",
V.yt_vis="isVisible",V.rcl="mwebInfo.responseContentLength",V.GetSettings_rid="requestIds",V.GetTrending_rid="requestIds",V.GetMusicSearchSuggestions_rid="requestIds",V.REQUEST_ID="requestIds",V),Lr="isContinuation isNavigation kabukiInfo.earlyBrowseRequestInfo.adopted kabukiInfo.isPrefetch kabukiInfo.isSecondaryNav isMonetized navigationRequestedSameUrl performanceNavigationTiming playerInfo.isPausedOnLoad prerollAllowed isRedSubscriber tvInfo.isMdx tvInfo.isPreloaded isVisible watchInfo.isPlaylist playbackRequiresTap".split(" "),
Mr={},Nr=(Mr.ccs="CANARY_STATE_",Mr.mver="MEASUREMENT_VERSION_",Mr.pis="PLAYER_INITIALIZED_STATE_",Mr.yt_pt="LATENCY_PLAYER_",Mr.pa="LATENCY_ACTION_",Mr.ctop="TOP_ENTITY_TYPE_",Mr.yt_vst="VIDEO_STREAM_TYPE_",Mr),Or="all_vc ap aq c cbr cbrand cbrver cmodel cos cosver cplatform ctheme cver ei l_an l_mm plid srt yt_fss yt_li vpst vpni2 vpil2 icrc icrt pa GetAccountOverview_rid GetHistory_rid cmt d_vpct d_vpnfi d_vpni nsru pc pfa pfeh pftr pnc prerender psc rc start tcrt tcrc ssr vpr vps yt_abt yt_fn yt_fs yt_pft yt_pre yt_pt yt_pvis ytu_pvis yt_ref yt_sts tds".split(" ");
function Pr(a){return Jr[a]||"LATENCY_ACTION_UNKNOWN"}
function Qr(a,b,c){c=Br(c);if(c.gelInfos)c.gelInfos[a]=!0;else{var d={};c.gelInfos=(d[a]=!0,d)}if(a.match("_rid")){var e=a.split("_rid")[0];a="REQUEST_ID"}if(a in Kr){c=Kr[a];0<=fb(Lr,c)&&(b=!!b);a in Nr&&"string"===typeof b&&(b=Nr[a]+b.toUpperCase());a=b;b=c.split(".");for(var f=d={},g=0;g<b.length-1;g++){var h=b[g];f[h]={};f=f[h]}f[b[b.length-1]]="requestIds"===c?[{id:a,endpoint:e}]:a;return jr({},d)}0<=fb(Or,a)||Tp(new Q("Unknown label logged with GEL CSI",a))}
;var W={LATENCY_ACTION_KIDS_PROFILE_SWITCHER:90,LATENCY_ACTION_OFFLINE_THUMBNAIL_TRANSFER:100,LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR_ASYNC:46,LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR:37,LATENCY_ACTION_SPINNER_DISPLAYED:14,LATENCY_ACTION_PLAYABILITY_CHECK:10,LATENCY_ACTION_PROCESS:9,LATENCY_ACTION_APP_STARTUP:5,LATENCY_ACTION_ABANDONED_DIRECT_PLAYBACK:154,LATENCY_ACTION_SHARE_VIDEO:153,LATENCY_ACTION_AD_TO_VIDEO_INT:152,LATENCY_ACTION_ABANDONED_BROWSE:151,LATENCY_ACTION_PLAYER_ROTATION:150,LATENCY_ACTION_SHOPPING_IN_APP:124,
LATENCY_ACTION_PLAYER_ATTESTATION:121,LATENCY_ACTION_PLAYER_SEEK:119,LATENCY_ACTION_SUPER_STICKER_BUY_FLOW:114,LATENCY_ACTION_BLOCKS_PERFORMANCE:148,LATENCY_ACTION_ASSISTANT_QUERY:138,LATENCY_ACTION_ASSISTANT_SETTINGS:137,LATENCY_ACTION_ENTITY_KEY_DESERIALIZATION_PERF:129,LATENCY_ACTION_ENTITY_KEY_SERIALIZATION_PERF:128,LATENCY_ACTION_PROOF_OF_ORIGIN_TOKEN_CREATE:127,LATENCY_ACTION_EMBEDS_SDK_INITIALIZATION:123,LATENCY_ACTION_NETWORKLESS_PERFORMANCE:122,LATENCY_ACTION_DOWNLOADS_EXPANSION:133,LATENCY_ACTION_ENTITY_TRANSFORM:131,
LATENCY_ACTION_DOWNLOADS_COMPATIBILITY_LAYER:96,LATENCY_ACTION_EMBEDS_SET_VIDEO:95,LATENCY_ACTION_SETTINGS:93,LATENCY_ACTION_ABANDONED_STARTUP:81,LATENCY_ACTION_MEDIA_BROWSER_ALARM_PLAY:80,LATENCY_ACTION_MEDIA_BROWSER_SEARCH:79,LATENCY_ACTION_MEDIA_BROWSER_LOAD_TREE:78,LATENCY_ACTION_WHO_IS_WATCHING:77,LATENCY_ACTION_CAST_LOAD_BY_ENTITY_TO_WATCH:76,LATENCY_ACTION_LITE_SWITCH_ACCOUNT:73,LATENCY_ACTION_ELEMENTS_PERFORMANCE:70,LATENCY_ACTION_LOCATION_SIGNAL_COLLECTION:69,LATENCY_ACTION_MODIFY_CHANNEL_NOTIFICATION:65,
LATENCY_ACTION_OFFLINE_STORE_START:61,LATENCY_ACTION_REEL_EDITOR:58,LATENCY_ACTION_CHANNEL_SUBSCRIBE:56,LATENCY_ACTION_CHANNEL_PREVIEW:55,LATENCY_ACTION_PREFETCH:52,LATENCY_ACTION_ABANDONED_WATCH:45,LATENCY_ACTION_LOAD_COMMENT_REPLIES:26,LATENCY_ACTION_LOAD_COMMENTS:25,LATENCY_ACTION_EDIT_COMMENT:24,LATENCY_ACTION_NEW_COMMENT:23,LATENCY_ACTION_OFFLINE_SHARING_RECEIVER_PAIRING:19,LATENCY_ACTION_EMBED:18,LATENCY_ACTION_MDX_LAUNCH:15,LATENCY_ACTION_RESOLVE_URL:13,LATENCY_ACTION_CAST_SPLASH:149,LATENCY_ACTION_MDX_CAST:120,
LATENCY_ACTION_MDX_COMMAND:12,LATENCY_ACTION_REEL_SELECT_SEGMENT:136,LATENCY_ACTION_ACCELERATED_EFFECTS:145,LATENCY_ACTION_UPLOAD_AUDIO_MIXER:147,LATENCY_ACTION_SHORTS_SEG_IMP_TRANSCODING:146,LATENCY_ACTION_SHORTS_AUDIO_PICKER_PLAYBACK:130,LATENCY_ACTION_SHORTS_WAVEFORM_DOWNLOAD:125,LATENCY_ACTION_SHORTS_VIDEO_INGESTION:155,LATENCY_ACTION_SHORTS_GALLERY:107,LATENCY_ACTION_SHORTS_TRIM:105,LATENCY_ACTION_SHORTS_EDIT:104,LATENCY_ACTION_SHORTS_CAMERA:103,LATENCY_ACTION_PARENT_TOOLS_DASHBOARD:102,LATENCY_ACTION_PARENT_TOOLS_COLLECTION:101,
LATENCY_ACTION_MUSIC_LOAD_RECOMMENDED_MEDIA_ITEMS:116,LATENCY_ACTION_MUSIC_LOAD_MEDIA_ITEMS:115,LATENCY_ACTION_MUSIC_ALBUM_DETAIL:72,LATENCY_ACTION_MUSIC_PLAYLIST_DETAIL:71,LATENCY_ACTION_CHIPS:68,LATENCY_ACTION_SEARCH_ZERO_STATE:67,LATENCY_ACTION_LIVE_PAGINATION:117,LATENCY_ACTION_LIVE:20,LATENCY_ACTION_PREBUFFER:40,LATENCY_ACTION_TENX:39,LATENCY_ACTION_KIDS_PROFILE_SETTINGS:94,LATENCY_ACTION_KIDS_WATCH_IT_AGAIN:92,LATENCY_ACTION_KIDS_SECRET_CODE:91,LATENCY_ACTION_KIDS_PARENT_PROFILE_SETTINGS:89,
LATENCY_ACTION_KIDS_ONBOARDING:88,LATENCY_ACTION_KIDS_VOICE_SEARCH:82,LATENCY_ACTION_KIDS_CURATED_COLLECTION:62,LATENCY_ACTION_KIDS_LIBRARY:53,LATENCY_ACTION_CREATOR_VIDEO_TRANSLATIONS:38,LATENCY_ACTION_CREATOR_VIDEO_MONETIZATION:74,LATENCY_ACTION_CREATOR_VIDEO_LIVE_STREAMING:141,LATENCY_ACTION_CREATOR_VIDEO_LIVE_SETTINGS:142,LATENCY_ACTION_CREATOR_VIDEO_EDITOR_ASYNC:51,LATENCY_ACTION_CREATOR_VIDEO_EDITOR:50,LATENCY_ACTION_CREATOR_VIDEO_EDIT:36,LATENCY_ACTION_CREATOR_VIDEO_COMMENTS:34,LATENCY_ACTION_CREATOR_VIDEO_ANALYTICS:33,
LATENCY_ACTION_CREATOR_POST_LIST:112,LATENCY_ACTION_CREATOR_POST_EDIT:110,LATENCY_ACTION_CREATOR_POST_COMMENTS:111,LATENCY_ACTION_CREATOR_LIVE_STREAMING:108,LATENCY_ACTION_CREATOR_DIALOG_UPLOADS:86,LATENCY_ACTION_CREATOR_DIALOG_COPYRIGHT_STRIKES:87,LATENCY_ACTION_CREATOR_CHANNEL_VIDEOS:32,LATENCY_ACTION_CREATOR_CHANNEL_TRANSLATIONS:48,LATENCY_ACTION_CREATOR_CHANNEL_PLAYLISTS:139,LATENCY_ACTION_CREATOR_CHANNEL_MUSIC:99,LATENCY_ACTION_CREATOR_CHANNEL_MONETIZATION:43,LATENCY_ACTION_CREATOR_CHANNEL_EDITING:113,
LATENCY_ACTION_CREATOR_CHANNEL_DASHBOARD:49,LATENCY_ACTION_CREATOR_CHANNEL_COPYRIGHT:44,LATENCY_ACTION_CREATOR_CHANNEL_COMMENTS:66,LATENCY_ACTION_CREATOR_CHANNEL_ANALYTICS:31,LATENCY_ACTION_CREATOR_ARTIST_PROFILE:85,LATENCY_ACTION_CREATOR_ARTIST_CONCERTS:84,LATENCY_ACTION_CREATOR_ARTIST_ANALYTICS:83,LATENCY_ACTION_CREATOR_ANALYTICS_EXPLORE:140,LATENCY_ACTION_STORYBOARD_THUMBNAILS:118,LATENCY_ACTION_SEARCH_THUMBNAILS:59,LATENCY_ACTION_ON_DEVICE_MODEL_DOWNLOAD:54,LATENCY_ACTION_VOICE_ASSISTANT:47,LATENCY_ACTION_SEARCH_UI:35,
LATENCY_ACTION_SUGGEST:30,LATENCY_ACTION_AUTO_SEARCH:126,LATENCY_ACTION_DOWNLOADS:98,LATENCY_ACTION_EXPLORE:75,LATENCY_ACTION_VIDEO_LIST:63,LATENCY_ACTION_HOME_RESUME:60,LATENCY_ACTION_SUBSCRIPTIONS_LIST:57,LATENCY_ACTION_THUMBNAIL_LOAD:42,LATENCY_ACTION_FIRST_THUMBNAIL_LOAD:29,LATENCY_ACTION_SUBSCRIPTIONS_FEED:109,LATENCY_ACTION_SUBSCRIPTIONS:28,LATENCY_ACTION_TRENDING:27,LATENCY_ACTION_LIBRARY:21,LATENCY_ACTION_VIDEO_THUMBNAIL:8,LATENCY_ACTION_SHOW_MORE:7,LATENCY_ACTION_VIDEO_PREVIEW:6,LATENCY_ACTION_PREBUFFER_VIDEO:144,
LATENCY_ACTION_PREFETCH_VIDEO:143,LATENCY_ACTION_DIRECT_PLAYBACK:132,LATENCY_ACTION_REEL_WATCH:41,LATENCY_ACTION_AD_TO_AD:22,LATENCY_ACTION_VIDEO_TO_AD:17,LATENCY_ACTION_AD_TO_VIDEO:16,LATENCY_ACTION_ONBOARDING:135,LATENCY_ACTION_LOGIN:97,LATENCY_ACTION_BROWSE:11,LATENCY_ACTION_CHANNELS:4,LATENCY_ACTION_WATCH:3,LATENCY_ACTION_RESULTS:2,LATENCY_ACTION_HOME:1,LATENCY_ACTION_STARTUP:106,LATENCY_ACTION_UNKNOWN:0};W[W.LATENCY_ACTION_KIDS_PROFILE_SWITCHER]="LATENCY_ACTION_KIDS_PROFILE_SWITCHER";
W[W.LATENCY_ACTION_OFFLINE_THUMBNAIL_TRANSFER]="LATENCY_ACTION_OFFLINE_THUMBNAIL_TRANSFER";W[W.LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR_ASYNC]="LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR_ASYNC";W[W.LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR]="LATENCY_ACTION_CREATOR_VIDEO_VIDEO_EDITOR";W[W.LATENCY_ACTION_SPINNER_DISPLAYED]="LATENCY_ACTION_SPINNER_DISPLAYED";W[W.LATENCY_ACTION_PLAYABILITY_CHECK]="LATENCY_ACTION_PLAYABILITY_CHECK";W[W.LATENCY_ACTION_PROCESS]="LATENCY_ACTION_PROCESS";
W[W.LATENCY_ACTION_APP_STARTUP]="LATENCY_ACTION_APP_STARTUP";W[W.LATENCY_ACTION_ABANDONED_DIRECT_PLAYBACK]="LATENCY_ACTION_ABANDONED_DIRECT_PLAYBACK";W[W.LATENCY_ACTION_SHARE_VIDEO]="LATENCY_ACTION_SHARE_VIDEO";W[W.LATENCY_ACTION_AD_TO_VIDEO_INT]="LATENCY_ACTION_AD_TO_VIDEO_INT";W[W.LATENCY_ACTION_ABANDONED_BROWSE]="LATENCY_ACTION_ABANDONED_BROWSE";W[W.LATENCY_ACTION_PLAYER_ROTATION]="LATENCY_ACTION_PLAYER_ROTATION";W[W.LATENCY_ACTION_SHOPPING_IN_APP]="LATENCY_ACTION_SHOPPING_IN_APP";
W[W.LATENCY_ACTION_PLAYER_ATTESTATION]="LATENCY_ACTION_PLAYER_ATTESTATION";W[W.LATENCY_ACTION_PLAYER_SEEK]="LATENCY_ACTION_PLAYER_SEEK";W[W.LATENCY_ACTION_SUPER_STICKER_BUY_FLOW]="LATENCY_ACTION_SUPER_STICKER_BUY_FLOW";W[W.LATENCY_ACTION_BLOCKS_PERFORMANCE]="LATENCY_ACTION_BLOCKS_PERFORMANCE";W[W.LATENCY_ACTION_ASSISTANT_QUERY]="LATENCY_ACTION_ASSISTANT_QUERY";W[W.LATENCY_ACTION_ASSISTANT_SETTINGS]="LATENCY_ACTION_ASSISTANT_SETTINGS";W[W.LATENCY_ACTION_ENTITY_KEY_DESERIALIZATION_PERF]="LATENCY_ACTION_ENTITY_KEY_DESERIALIZATION_PERF";
W[W.LATENCY_ACTION_ENTITY_KEY_SERIALIZATION_PERF]="LATENCY_ACTION_ENTITY_KEY_SERIALIZATION_PERF";W[W.LATENCY_ACTION_PROOF_OF_ORIGIN_TOKEN_CREATE]="LATENCY_ACTION_PROOF_OF_ORIGIN_TOKEN_CREATE";W[W.LATENCY_ACTION_EMBEDS_SDK_INITIALIZATION]="LATENCY_ACTION_EMBEDS_SDK_INITIALIZATION";W[W.LATENCY_ACTION_NETWORKLESS_PERFORMANCE]="LATENCY_ACTION_NETWORKLESS_PERFORMANCE";W[W.LATENCY_ACTION_DOWNLOADS_EXPANSION]="LATENCY_ACTION_DOWNLOADS_EXPANSION";W[W.LATENCY_ACTION_ENTITY_TRANSFORM]="LATENCY_ACTION_ENTITY_TRANSFORM";
W[W.LATENCY_ACTION_DOWNLOADS_COMPATIBILITY_LAYER]="LATENCY_ACTION_DOWNLOADS_COMPATIBILITY_LAYER";W[W.LATENCY_ACTION_EMBEDS_SET_VIDEO]="LATENCY_ACTION_EMBEDS_SET_VIDEO";W[W.LATENCY_ACTION_SETTINGS]="LATENCY_ACTION_SETTINGS";W[W.LATENCY_ACTION_ABANDONED_STARTUP]="LATENCY_ACTION_ABANDONED_STARTUP";W[W.LATENCY_ACTION_MEDIA_BROWSER_ALARM_PLAY]="LATENCY_ACTION_MEDIA_BROWSER_ALARM_PLAY";W[W.LATENCY_ACTION_MEDIA_BROWSER_SEARCH]="LATENCY_ACTION_MEDIA_BROWSER_SEARCH";
W[W.LATENCY_ACTION_MEDIA_BROWSER_LOAD_TREE]="LATENCY_ACTION_MEDIA_BROWSER_LOAD_TREE";W[W.LATENCY_ACTION_WHO_IS_WATCHING]="LATENCY_ACTION_WHO_IS_WATCHING";W[W.LATENCY_ACTION_CAST_LOAD_BY_ENTITY_TO_WATCH]="LATENCY_ACTION_CAST_LOAD_BY_ENTITY_TO_WATCH";W[W.LATENCY_ACTION_LITE_SWITCH_ACCOUNT]="LATENCY_ACTION_LITE_SWITCH_ACCOUNT";W[W.LATENCY_ACTION_ELEMENTS_PERFORMANCE]="LATENCY_ACTION_ELEMENTS_PERFORMANCE";W[W.LATENCY_ACTION_LOCATION_SIGNAL_COLLECTION]="LATENCY_ACTION_LOCATION_SIGNAL_COLLECTION";
W[W.LATENCY_ACTION_MODIFY_CHANNEL_NOTIFICATION]="LATENCY_ACTION_MODIFY_CHANNEL_NOTIFICATION";W[W.LATENCY_ACTION_OFFLINE_STORE_START]="LATENCY_ACTION_OFFLINE_STORE_START";W[W.LATENCY_ACTION_REEL_EDITOR]="LATENCY_ACTION_REEL_EDITOR";W[W.LATENCY_ACTION_CHANNEL_SUBSCRIBE]="LATENCY_ACTION_CHANNEL_SUBSCRIBE";W[W.LATENCY_ACTION_CHANNEL_PREVIEW]="LATENCY_ACTION_CHANNEL_PREVIEW";W[W.LATENCY_ACTION_PREFETCH]="LATENCY_ACTION_PREFETCH";W[W.LATENCY_ACTION_ABANDONED_WATCH]="LATENCY_ACTION_ABANDONED_WATCH";
W[W.LATENCY_ACTION_LOAD_COMMENT_REPLIES]="LATENCY_ACTION_LOAD_COMMENT_REPLIES";W[W.LATENCY_ACTION_LOAD_COMMENTS]="LATENCY_ACTION_LOAD_COMMENTS";W[W.LATENCY_ACTION_EDIT_COMMENT]="LATENCY_ACTION_EDIT_COMMENT";W[W.LATENCY_ACTION_NEW_COMMENT]="LATENCY_ACTION_NEW_COMMENT";W[W.LATENCY_ACTION_OFFLINE_SHARING_RECEIVER_PAIRING]="LATENCY_ACTION_OFFLINE_SHARING_RECEIVER_PAIRING";W[W.LATENCY_ACTION_EMBED]="LATENCY_ACTION_EMBED";W[W.LATENCY_ACTION_MDX_LAUNCH]="LATENCY_ACTION_MDX_LAUNCH";
W[W.LATENCY_ACTION_RESOLVE_URL]="LATENCY_ACTION_RESOLVE_URL";W[W.LATENCY_ACTION_CAST_SPLASH]="LATENCY_ACTION_CAST_SPLASH";W[W.LATENCY_ACTION_MDX_CAST]="LATENCY_ACTION_MDX_CAST";W[W.LATENCY_ACTION_MDX_COMMAND]="LATENCY_ACTION_MDX_COMMAND";W[W.LATENCY_ACTION_REEL_SELECT_SEGMENT]="LATENCY_ACTION_REEL_SELECT_SEGMENT";W[W.LATENCY_ACTION_ACCELERATED_EFFECTS]="LATENCY_ACTION_ACCELERATED_EFFECTS";W[W.LATENCY_ACTION_UPLOAD_AUDIO_MIXER]="LATENCY_ACTION_UPLOAD_AUDIO_MIXER";
W[W.LATENCY_ACTION_SHORTS_SEG_IMP_TRANSCODING]="LATENCY_ACTION_SHORTS_SEG_IMP_TRANSCODING";W[W.LATENCY_ACTION_SHORTS_AUDIO_PICKER_PLAYBACK]="LATENCY_ACTION_SHORTS_AUDIO_PICKER_PLAYBACK";W[W.LATENCY_ACTION_SHORTS_WAVEFORM_DOWNLOAD]="LATENCY_ACTION_SHORTS_WAVEFORM_DOWNLOAD";W[W.LATENCY_ACTION_SHORTS_VIDEO_INGESTION]="LATENCY_ACTION_SHORTS_VIDEO_INGESTION";W[W.LATENCY_ACTION_SHORTS_GALLERY]="LATENCY_ACTION_SHORTS_GALLERY";W[W.LATENCY_ACTION_SHORTS_TRIM]="LATENCY_ACTION_SHORTS_TRIM";
W[W.LATENCY_ACTION_SHORTS_EDIT]="LATENCY_ACTION_SHORTS_EDIT";W[W.LATENCY_ACTION_SHORTS_CAMERA]="LATENCY_ACTION_SHORTS_CAMERA";W[W.LATENCY_ACTION_PARENT_TOOLS_DASHBOARD]="LATENCY_ACTION_PARENT_TOOLS_DASHBOARD";W[W.LATENCY_ACTION_PARENT_TOOLS_COLLECTION]="LATENCY_ACTION_PARENT_TOOLS_COLLECTION";W[W.LATENCY_ACTION_MUSIC_LOAD_RECOMMENDED_MEDIA_ITEMS]="LATENCY_ACTION_MUSIC_LOAD_RECOMMENDED_MEDIA_ITEMS";W[W.LATENCY_ACTION_MUSIC_LOAD_MEDIA_ITEMS]="LATENCY_ACTION_MUSIC_LOAD_MEDIA_ITEMS";
W[W.LATENCY_ACTION_MUSIC_ALBUM_DETAIL]="LATENCY_ACTION_MUSIC_ALBUM_DETAIL";W[W.LATENCY_ACTION_MUSIC_PLAYLIST_DETAIL]="LATENCY_ACTION_MUSIC_PLAYLIST_DETAIL";W[W.LATENCY_ACTION_CHIPS]="LATENCY_ACTION_CHIPS";W[W.LATENCY_ACTION_SEARCH_ZERO_STATE]="LATENCY_ACTION_SEARCH_ZERO_STATE";W[W.LATENCY_ACTION_LIVE_PAGINATION]="LATENCY_ACTION_LIVE_PAGINATION";W[W.LATENCY_ACTION_LIVE]="LATENCY_ACTION_LIVE";W[W.LATENCY_ACTION_PREBUFFER]="LATENCY_ACTION_PREBUFFER";W[W.LATENCY_ACTION_TENX]="LATENCY_ACTION_TENX";
W[W.LATENCY_ACTION_KIDS_PROFILE_SETTINGS]="LATENCY_ACTION_KIDS_PROFILE_SETTINGS";W[W.LATENCY_ACTION_KIDS_WATCH_IT_AGAIN]="LATENCY_ACTION_KIDS_WATCH_IT_AGAIN";W[W.LATENCY_ACTION_KIDS_SECRET_CODE]="LATENCY_ACTION_KIDS_SECRET_CODE";W[W.LATENCY_ACTION_KIDS_PARENT_PROFILE_SETTINGS]="LATENCY_ACTION_KIDS_PARENT_PROFILE_SETTINGS";W[W.LATENCY_ACTION_KIDS_ONBOARDING]="LATENCY_ACTION_KIDS_ONBOARDING";W[W.LATENCY_ACTION_KIDS_VOICE_SEARCH]="LATENCY_ACTION_KIDS_VOICE_SEARCH";
W[W.LATENCY_ACTION_KIDS_CURATED_COLLECTION]="LATENCY_ACTION_KIDS_CURATED_COLLECTION";W[W.LATENCY_ACTION_KIDS_LIBRARY]="LATENCY_ACTION_KIDS_LIBRARY";W[W.LATENCY_ACTION_CREATOR_VIDEO_TRANSLATIONS]="LATENCY_ACTION_CREATOR_VIDEO_TRANSLATIONS";W[W.LATENCY_ACTION_CREATOR_VIDEO_MONETIZATION]="LATENCY_ACTION_CREATOR_VIDEO_MONETIZATION";W[W.LATENCY_ACTION_CREATOR_VIDEO_LIVE_STREAMING]="LATENCY_ACTION_CREATOR_VIDEO_LIVE_STREAMING";W[W.LATENCY_ACTION_CREATOR_VIDEO_LIVE_SETTINGS]="LATENCY_ACTION_CREATOR_VIDEO_LIVE_SETTINGS";
W[W.LATENCY_ACTION_CREATOR_VIDEO_EDITOR_ASYNC]="LATENCY_ACTION_CREATOR_VIDEO_EDITOR_ASYNC";W[W.LATENCY_ACTION_CREATOR_VIDEO_EDITOR]="LATENCY_ACTION_CREATOR_VIDEO_EDITOR";W[W.LATENCY_ACTION_CREATOR_VIDEO_EDIT]="LATENCY_ACTION_CREATOR_VIDEO_EDIT";W[W.LATENCY_ACTION_CREATOR_VIDEO_COMMENTS]="LATENCY_ACTION_CREATOR_VIDEO_COMMENTS";W[W.LATENCY_ACTION_CREATOR_VIDEO_ANALYTICS]="LATENCY_ACTION_CREATOR_VIDEO_ANALYTICS";W[W.LATENCY_ACTION_CREATOR_POST_LIST]="LATENCY_ACTION_CREATOR_POST_LIST";
W[W.LATENCY_ACTION_CREATOR_POST_EDIT]="LATENCY_ACTION_CREATOR_POST_EDIT";W[W.LATENCY_ACTION_CREATOR_POST_COMMENTS]="LATENCY_ACTION_CREATOR_POST_COMMENTS";W[W.LATENCY_ACTION_CREATOR_LIVE_STREAMING]="LATENCY_ACTION_CREATOR_LIVE_STREAMING";W[W.LATENCY_ACTION_CREATOR_DIALOG_UPLOADS]="LATENCY_ACTION_CREATOR_DIALOG_UPLOADS";W[W.LATENCY_ACTION_CREATOR_DIALOG_COPYRIGHT_STRIKES]="LATENCY_ACTION_CREATOR_DIALOG_COPYRIGHT_STRIKES";W[W.LATENCY_ACTION_CREATOR_CHANNEL_VIDEOS]="LATENCY_ACTION_CREATOR_CHANNEL_VIDEOS";
W[W.LATENCY_ACTION_CREATOR_CHANNEL_TRANSLATIONS]="LATENCY_ACTION_CREATOR_CHANNEL_TRANSLATIONS";W[W.LATENCY_ACTION_CREATOR_CHANNEL_PLAYLISTS]="LATENCY_ACTION_CREATOR_CHANNEL_PLAYLISTS";W[W.LATENCY_ACTION_CREATOR_CHANNEL_MUSIC]="LATENCY_ACTION_CREATOR_CHANNEL_MUSIC";W[W.LATENCY_ACTION_CREATOR_CHANNEL_MONETIZATION]="LATENCY_ACTION_CREATOR_CHANNEL_MONETIZATION";W[W.LATENCY_ACTION_CREATOR_CHANNEL_EDITING]="LATENCY_ACTION_CREATOR_CHANNEL_EDITING";W[W.LATENCY_ACTION_CREATOR_CHANNEL_DASHBOARD]="LATENCY_ACTION_CREATOR_CHANNEL_DASHBOARD";
W[W.LATENCY_ACTION_CREATOR_CHANNEL_COPYRIGHT]="LATENCY_ACTION_CREATOR_CHANNEL_COPYRIGHT";W[W.LATENCY_ACTION_CREATOR_CHANNEL_COMMENTS]="LATENCY_ACTION_CREATOR_CHANNEL_COMMENTS";W[W.LATENCY_ACTION_CREATOR_CHANNEL_ANALYTICS]="LATENCY_ACTION_CREATOR_CHANNEL_ANALYTICS";W[W.LATENCY_ACTION_CREATOR_ARTIST_PROFILE]="LATENCY_ACTION_CREATOR_ARTIST_PROFILE";W[W.LATENCY_ACTION_CREATOR_ARTIST_CONCERTS]="LATENCY_ACTION_CREATOR_ARTIST_CONCERTS";W[W.LATENCY_ACTION_CREATOR_ARTIST_ANALYTICS]="LATENCY_ACTION_CREATOR_ARTIST_ANALYTICS";
W[W.LATENCY_ACTION_CREATOR_ANALYTICS_EXPLORE]="LATENCY_ACTION_CREATOR_ANALYTICS_EXPLORE";W[W.LATENCY_ACTION_STORYBOARD_THUMBNAILS]="LATENCY_ACTION_STORYBOARD_THUMBNAILS";W[W.LATENCY_ACTION_SEARCH_THUMBNAILS]="LATENCY_ACTION_SEARCH_THUMBNAILS";W[W.LATENCY_ACTION_ON_DEVICE_MODEL_DOWNLOAD]="LATENCY_ACTION_ON_DEVICE_MODEL_DOWNLOAD";W[W.LATENCY_ACTION_VOICE_ASSISTANT]="LATENCY_ACTION_VOICE_ASSISTANT";W[W.LATENCY_ACTION_SEARCH_UI]="LATENCY_ACTION_SEARCH_UI";W[W.LATENCY_ACTION_SUGGEST]="LATENCY_ACTION_SUGGEST";
W[W.LATENCY_ACTION_AUTO_SEARCH]="LATENCY_ACTION_AUTO_SEARCH";W[W.LATENCY_ACTION_DOWNLOADS]="LATENCY_ACTION_DOWNLOADS";W[W.LATENCY_ACTION_EXPLORE]="LATENCY_ACTION_EXPLORE";W[W.LATENCY_ACTION_VIDEO_LIST]="LATENCY_ACTION_VIDEO_LIST";W[W.LATENCY_ACTION_HOME_RESUME]="LATENCY_ACTION_HOME_RESUME";W[W.LATENCY_ACTION_SUBSCRIPTIONS_LIST]="LATENCY_ACTION_SUBSCRIPTIONS_LIST";W[W.LATENCY_ACTION_THUMBNAIL_LOAD]="LATENCY_ACTION_THUMBNAIL_LOAD";W[W.LATENCY_ACTION_FIRST_THUMBNAIL_LOAD]="LATENCY_ACTION_FIRST_THUMBNAIL_LOAD";
W[W.LATENCY_ACTION_SUBSCRIPTIONS_FEED]="LATENCY_ACTION_SUBSCRIPTIONS_FEED";W[W.LATENCY_ACTION_SUBSCRIPTIONS]="LATENCY_ACTION_SUBSCRIPTIONS";W[W.LATENCY_ACTION_TRENDING]="LATENCY_ACTION_TRENDING";W[W.LATENCY_ACTION_LIBRARY]="LATENCY_ACTION_LIBRARY";W[W.LATENCY_ACTION_VIDEO_THUMBNAIL]="LATENCY_ACTION_VIDEO_THUMBNAIL";W[W.LATENCY_ACTION_SHOW_MORE]="LATENCY_ACTION_SHOW_MORE";W[W.LATENCY_ACTION_VIDEO_PREVIEW]="LATENCY_ACTION_VIDEO_PREVIEW";W[W.LATENCY_ACTION_PREBUFFER_VIDEO]="LATENCY_ACTION_PREBUFFER_VIDEO";
W[W.LATENCY_ACTION_PREFETCH_VIDEO]="LATENCY_ACTION_PREFETCH_VIDEO";W[W.LATENCY_ACTION_DIRECT_PLAYBACK]="LATENCY_ACTION_DIRECT_PLAYBACK";W[W.LATENCY_ACTION_REEL_WATCH]="LATENCY_ACTION_REEL_WATCH";W[W.LATENCY_ACTION_AD_TO_AD]="LATENCY_ACTION_AD_TO_AD";W[W.LATENCY_ACTION_VIDEO_TO_AD]="LATENCY_ACTION_VIDEO_TO_AD";W[W.LATENCY_ACTION_AD_TO_VIDEO]="LATENCY_ACTION_AD_TO_VIDEO";W[W.LATENCY_ACTION_ONBOARDING]="LATENCY_ACTION_ONBOARDING";W[W.LATENCY_ACTION_LOGIN]="LATENCY_ACTION_LOGIN";
W[W.LATENCY_ACTION_BROWSE]="LATENCY_ACTION_BROWSE";W[W.LATENCY_ACTION_CHANNELS]="LATENCY_ACTION_CHANNELS";W[W.LATENCY_ACTION_WATCH]="LATENCY_ACTION_WATCH";W[W.LATENCY_ACTION_RESULTS]="LATENCY_ACTION_RESULTS";W[W.LATENCY_ACTION_HOME]="LATENCY_ACTION_HOME";W[W.LATENCY_ACTION_STARTUP]="LATENCY_ACTION_STARTUP";W[W.LATENCY_ACTION_UNKNOWN]="LATENCY_ACTION_UNKNOWN";var Rr={LATENCY_NETWORK_MOBILE:2,LATENCY_NETWORK_WIFI:1,LATENCY_NETWORK_UNKNOWN:0};Rr[Rr.LATENCY_NETWORK_MOBILE]="LATENCY_NETWORK_MOBILE";
Rr[Rr.LATENCY_NETWORK_WIFI]="LATENCY_NETWORK_WIFI";Rr[Rr.LATENCY_NETWORK_UNKNOWN]="LATENCY_NETWORK_UNKNOWN";var X={CONN_INVALID:31,CONN_CELLULAR_5G_NSA:12,CONN_CELLULAR_5G_SA:11,CONN_WIFI_METERED:10,CONN_CELLULAR_5G:9,CONN_DISCO:8,CONN_CELLULAR_UNKNOWN:7,CONN_CELLULAR_4G:6,CONN_CELLULAR_3G:5,CONN_CELLULAR_2G:4,CONN_WIFI:3,CONN_NONE:2,CONN_UNKNOWN:1,CONN_DEFAULT:0};X[X.CONN_INVALID]="CONN_INVALID";X[X.CONN_CELLULAR_5G_NSA]="CONN_CELLULAR_5G_NSA";X[X.CONN_CELLULAR_5G_SA]="CONN_CELLULAR_5G_SA";
X[X.CONN_WIFI_METERED]="CONN_WIFI_METERED";X[X.CONN_CELLULAR_5G]="CONN_CELLULAR_5G";X[X.CONN_DISCO]="CONN_DISCO";X[X.CONN_CELLULAR_UNKNOWN]="CONN_CELLULAR_UNKNOWN";X[X.CONN_CELLULAR_4G]="CONN_CELLULAR_4G";X[X.CONN_CELLULAR_3G]="CONN_CELLULAR_3G";X[X.CONN_CELLULAR_2G]="CONN_CELLULAR_2G";X[X.CONN_WIFI]="CONN_WIFI";X[X.CONN_NONE]="CONN_NONE";X[X.CONN_UNKNOWN]="CONN_UNKNOWN";X[X.CONN_DEFAULT]="CONN_DEFAULT";
var Y={DETAILED_NETWORK_TYPE_NR_NSA:126,DETAILED_NETWORK_TYPE_NR_SA:125,DETAILED_NETWORK_TYPE_INTERNAL_WIFI_IMPAIRED:124,DETAILED_NETWORK_TYPE_APP_WIFI_HOTSPOT:123,DETAILED_NETWORK_TYPE_DISCONNECTED:122,DETAILED_NETWORK_TYPE_NON_MOBILE_UNKNOWN:121,DETAILED_NETWORK_TYPE_MOBILE_UNKNOWN:120,DETAILED_NETWORK_TYPE_WIMAX:119,DETAILED_NETWORK_TYPE_ETHERNET:118,DETAILED_NETWORK_TYPE_BLUETOOTH:117,DETAILED_NETWORK_TYPE_WIFI:116,DETAILED_NETWORK_TYPE_LTE:115,DETAILED_NETWORK_TYPE_HSPAP:114,DETAILED_NETWORK_TYPE_EHRPD:113,
DETAILED_NETWORK_TYPE_EVDO_B:112,DETAILED_NETWORK_TYPE_UMTS:111,DETAILED_NETWORK_TYPE_IDEN:110,DETAILED_NETWORK_TYPE_HSUPA:109,DETAILED_NETWORK_TYPE_HSPA:108,DETAILED_NETWORK_TYPE_HSDPA:107,DETAILED_NETWORK_TYPE_EVDO_A:106,DETAILED_NETWORK_TYPE_EVDO_0:105,DETAILED_NETWORK_TYPE_CDMA:104,DETAILED_NETWORK_TYPE_1_X_RTT:103,DETAILED_NETWORK_TYPE_GPRS:102,DETAILED_NETWORK_TYPE_EDGE:101,DETAILED_NETWORK_TYPE_UNKNOWN:0};Y[Y.DETAILED_NETWORK_TYPE_NR_NSA]="DETAILED_NETWORK_TYPE_NR_NSA";
Y[Y.DETAILED_NETWORK_TYPE_NR_SA]="DETAILED_NETWORK_TYPE_NR_SA";Y[Y.DETAILED_NETWORK_TYPE_INTERNAL_WIFI_IMPAIRED]="DETAILED_NETWORK_TYPE_INTERNAL_WIFI_IMPAIRED";Y[Y.DETAILED_NETWORK_TYPE_APP_WIFI_HOTSPOT]="DETAILED_NETWORK_TYPE_APP_WIFI_HOTSPOT";Y[Y.DETAILED_NETWORK_TYPE_DISCONNECTED]="DETAILED_NETWORK_TYPE_DISCONNECTED";Y[Y.DETAILED_NETWORK_TYPE_NON_MOBILE_UNKNOWN]="DETAILED_NETWORK_TYPE_NON_MOBILE_UNKNOWN";Y[Y.DETAILED_NETWORK_TYPE_MOBILE_UNKNOWN]="DETAILED_NETWORK_TYPE_MOBILE_UNKNOWN";
Y[Y.DETAILED_NETWORK_TYPE_WIMAX]="DETAILED_NETWORK_TYPE_WIMAX";Y[Y.DETAILED_NETWORK_TYPE_ETHERNET]="DETAILED_NETWORK_TYPE_ETHERNET";Y[Y.DETAILED_NETWORK_TYPE_BLUETOOTH]="DETAILED_NETWORK_TYPE_BLUETOOTH";Y[Y.DETAILED_NETWORK_TYPE_WIFI]="DETAILED_NETWORK_TYPE_WIFI";Y[Y.DETAILED_NETWORK_TYPE_LTE]="DETAILED_NETWORK_TYPE_LTE";Y[Y.DETAILED_NETWORK_TYPE_HSPAP]="DETAILED_NETWORK_TYPE_HSPAP";Y[Y.DETAILED_NETWORK_TYPE_EHRPD]="DETAILED_NETWORK_TYPE_EHRPD";Y[Y.DETAILED_NETWORK_TYPE_EVDO_B]="DETAILED_NETWORK_TYPE_EVDO_B";
Y[Y.DETAILED_NETWORK_TYPE_UMTS]="DETAILED_NETWORK_TYPE_UMTS";Y[Y.DETAILED_NETWORK_TYPE_IDEN]="DETAILED_NETWORK_TYPE_IDEN";Y[Y.DETAILED_NETWORK_TYPE_HSUPA]="DETAILED_NETWORK_TYPE_HSUPA";Y[Y.DETAILED_NETWORK_TYPE_HSPA]="DETAILED_NETWORK_TYPE_HSPA";Y[Y.DETAILED_NETWORK_TYPE_HSDPA]="DETAILED_NETWORK_TYPE_HSDPA";Y[Y.DETAILED_NETWORK_TYPE_EVDO_A]="DETAILED_NETWORK_TYPE_EVDO_A";Y[Y.DETAILED_NETWORK_TYPE_EVDO_0]="DETAILED_NETWORK_TYPE_EVDO_0";Y[Y.DETAILED_NETWORK_TYPE_CDMA]="DETAILED_NETWORK_TYPE_CDMA";
Y[Y.DETAILED_NETWORK_TYPE_1_X_RTT]="DETAILED_NETWORK_TYPE_1_X_RTT";Y[Y.DETAILED_NETWORK_TYPE_GPRS]="DETAILED_NETWORK_TYPE_GPRS";Y[Y.DETAILED_NETWORK_TYPE_EDGE]="DETAILED_NETWORK_TYPE_EDGE";Y[Y.DETAILED_NETWORK_TYPE_UNKNOWN]="DETAILED_NETWORK_TYPE_UNKNOWN";var Sr={LATENCY_PLAYER_RTSP:7,LATENCY_PLAYER_HTML5_INLINE:6,LATENCY_PLAYER_HTML5_FULLSCREEN:5,LATENCY_PLAYER_HTML5:4,LATENCY_PLAYER_FRAMEWORK:3,LATENCY_PLAYER_FLASH:2,LATENCY_PLAYER_EXO:1,LATENCY_PLAYER_UNKNOWN:0};Sr[Sr.LATENCY_PLAYER_RTSP]="LATENCY_PLAYER_RTSP";
Sr[Sr.LATENCY_PLAYER_HTML5_INLINE]="LATENCY_PLAYER_HTML5_INLINE";Sr[Sr.LATENCY_PLAYER_HTML5_FULLSCREEN]="LATENCY_PLAYER_HTML5_FULLSCREEN";Sr[Sr.LATENCY_PLAYER_HTML5]="LATENCY_PLAYER_HTML5";Sr[Sr.LATENCY_PLAYER_FRAMEWORK]="LATENCY_PLAYER_FRAMEWORK";Sr[Sr.LATENCY_PLAYER_FLASH]="LATENCY_PLAYER_FLASH";Sr[Sr.LATENCY_PLAYER_EXO]="LATENCY_PLAYER_EXO";Sr[Sr.LATENCY_PLAYER_UNKNOWN]="LATENCY_PLAYER_UNKNOWN";
var Tr={LATENCY_AD_BREAK_TYPE_POSTROLL:3,LATENCY_AD_BREAK_TYPE_MIDROLL:2,LATENCY_AD_BREAK_TYPE_PREROLL:1,LATENCY_AD_BREAK_TYPE_UNKNOWN:0};Tr[Tr.LATENCY_AD_BREAK_TYPE_POSTROLL]="LATENCY_AD_BREAK_TYPE_POSTROLL";Tr[Tr.LATENCY_AD_BREAK_TYPE_MIDROLL]="LATENCY_AD_BREAK_TYPE_MIDROLL";Tr[Tr.LATENCY_AD_BREAK_TYPE_PREROLL]="LATENCY_AD_BREAK_TYPE_PREROLL";Tr[Tr.LATENCY_AD_BREAK_TYPE_UNKNOWN]="LATENCY_AD_BREAK_TYPE_UNKNOWN";var Ur={LATENCY_ACTION_ERROR_STARTUP_TIMEOUT:1,LATENCY_ACTION_ERROR_UNSPECIFIED:0};
Ur[Ur.LATENCY_ACTION_ERROR_STARTUP_TIMEOUT]="LATENCY_ACTION_ERROR_STARTUP_TIMEOUT";Ur[Ur.LATENCY_ACTION_ERROR_UNSPECIFIED]="LATENCY_ACTION_ERROR_UNSPECIFIED";var Vr={LIVE_STREAM_MODE_WINDOW:5,LIVE_STREAM_MODE_POST:4,LIVE_STREAM_MODE_LP:3,LIVE_STREAM_MODE_LIVE:2,LIVE_STREAM_MODE_DVR:1,LIVE_STREAM_MODE_UNKNOWN:0};Vr[Vr.LIVE_STREAM_MODE_WINDOW]="LIVE_STREAM_MODE_WINDOW";Vr[Vr.LIVE_STREAM_MODE_POST]="LIVE_STREAM_MODE_POST";Vr[Vr.LIVE_STREAM_MODE_LP]="LIVE_STREAM_MODE_LP";
Vr[Vr.LIVE_STREAM_MODE_LIVE]="LIVE_STREAM_MODE_LIVE";Vr[Vr.LIVE_STREAM_MODE_DVR]="LIVE_STREAM_MODE_DVR";Vr[Vr.LIVE_STREAM_MODE_UNKNOWN]="LIVE_STREAM_MODE_UNKNOWN";var Wr={VIDEO_STREAM_TYPE_VOD:3,VIDEO_STREAM_TYPE_DVR:2,VIDEO_STREAM_TYPE_LIVE:1,VIDEO_STREAM_TYPE_UNSPECIFIED:0};Wr[Wr.VIDEO_STREAM_TYPE_VOD]="VIDEO_STREAM_TYPE_VOD";Wr[Wr.VIDEO_STREAM_TYPE_DVR]="VIDEO_STREAM_TYPE_DVR";Wr[Wr.VIDEO_STREAM_TYPE_LIVE]="VIDEO_STREAM_TYPE_LIVE";Wr[Wr.VIDEO_STREAM_TYPE_UNSPECIFIED]="VIDEO_STREAM_TYPE_UNSPECIFIED";
var Xr={YT_IDB_TRANSACTION_TYPE_READ:2,YT_IDB_TRANSACTION_TYPE_WRITE:1,YT_IDB_TRANSACTION_TYPE_UNKNOWN:0};Xr[Xr.YT_IDB_TRANSACTION_TYPE_READ]="YT_IDB_TRANSACTION_TYPE_READ";Xr[Xr.YT_IDB_TRANSACTION_TYPE_WRITE]="YT_IDB_TRANSACTION_TYPE_WRITE";Xr[Xr.YT_IDB_TRANSACTION_TYPE_UNKNOWN]="YT_IDB_TRANSACTION_TYPE_UNKNOWN";var Yr={PLAYER_ROTATION_TYPE_PORTRAIT_TO_FULLSCREEN:2,PLAYER_ROTATION_TYPE_FULLSCREEN_TO_PORTRAIT:1,PLAYER_ROTATION_TYPE_UNKNOWN:0};Yr[Yr.PLAYER_ROTATION_TYPE_PORTRAIT_TO_FULLSCREEN]="PLAYER_ROTATION_TYPE_PORTRAIT_TO_FULLSCREEN";
Yr[Yr.PLAYER_ROTATION_TYPE_FULLSCREEN_TO_PORTRAIT]="PLAYER_ROTATION_TYPE_FULLSCREEN_TO_PORTRAIT";Yr[Yr.PLAYER_ROTATION_TYPE_UNKNOWN]="PLAYER_ROTATION_TYPE_UNKNOWN";var Zr="actionVisualElement spinnerInfo resourceInfo playerInfo commentInfo mdxInfo watchInfo thumbnailLoadInfo creatorInfo unpluggedInfo reelInfo subscriptionsFeedInfo requestIds mediaBrowserActionInfo musicLoadActionInfo shoppingInfo prefetchInfo accelerationSession webInfo tvInfo kabukiInfo mwebInfo musicInfo".split(" ");var $r=x.ytLoggingLatencyUsageStats_||{};y("ytLoggingLatencyUsageStats_",$r,void 0);function as(){this.h=0}
function bs(){as.h||(as.h=new as);return as.h}
as.prototype.tick=function(a,b,c,d){cs(this,"tick_"+a+"_"+b)||(c={timestamp:c,cttAuthInfo:d},M("web_csi_via_jspb")?(d=new zh,D(d,1,a),D(d,2,b),a=new Ch,od(a,5,Dh,d),Ep(a,c)):ok("latencyActionTicked",{tickName:a,clientActionNonce:b},c))};
as.prototype.info=function(a,b,c){var d=Object.keys(a).join("");cs(this,"info_"+d+"_"+b)||(a=Object.assign({},a),a.clientActionNonce=b,ok("latencyActionInfo",a,{cttAuthInfo:c}))};
as.prototype.jspbInfo=function(a,b,c){for(var d="",e=0;e<a.toJSON().length;e++)void 0!==a.toJSON()[e]&&(d=0===e?d.concat(""+e):d.concat("_"+e));cs(this,"info_"+d+"_"+b)||(D(a,2,b),b={cttAuthInfo:c},c=new Ch,od(c,7,Dh,a),Ep(c,b))};
as.prototype.span=function(a,b,c){var d=Object.keys(a).join("");cs(this,"span_"+d+"_"+b)||(a.clientActionNonce=b,ok("latencyActionSpan",a,{cttAuthInfo:c}))};
function cs(a,b){$r[b]=$r[b]||{count:0};var c=$r[b];c.count++;c.time=P();a.h||(a.h=Yj(function(){var d=P(),e;for(e in $r)$r[e]&&6E4<d-$r[e].time&&delete $r[e];a&&(a.h=0)},5E3));
return 5<c.count?(6===c.count&&1>1E5*Math.random()&&(c=new Q("CSI data exceeded logging limit with key",b.split("_")),0<=b.indexOf("plev")||Tp(c)),!0):!1}
;function ds(){var a=["ol"];Ir("").info.actionType="embed";a&&Zh("TIMING_AFT_KEYS",a);Zh("TIMING_ACTION","embed");es();a=Ar();var b=Cr();if("cold"===a.yt_lt||"cold"===b.loadType){var c=vr(),d=Br();d=d.gelTicks?d.gelTicks:d.gelTicks={};for(var e in c)e in d||Z(e,c[e]);e={};c=!1;d=p(Object.keys(a));for(var f=d.next();!f.done;f=d.next())f=f.value,(f=Qr(f,a[f]))&&!Fr(Cr(void 0),f)&&(jr(b,f),jr(e,f),c=!0);c&&fs(e)}Za("ytglobal.timingready_",!0);a=$h("TIMING_ACTION");z("ytglobal.timingready_")&&a&&"_start"in
vr(void 0)&&ur()&&Er()}
function gs(a,b,c,d){null!==b&&(Ar(c)[a]=b,(a=Qr(a,b,c))&&fs(a,c,d))}
function fs(a,b,c){if(!M("web_csi_via_jspb")||(void 0===c?0:c))c=Ir(b||""),jr(c.info,a),jr(Cr(b),a),c=Dr(b),b=zr(b).cttAuthInfo,bs().info(a,c,b);else{c=new vh;var d=Object.keys(a);a=Object.values(a);for(var e=0;e<d.length;e++){var f=d[e];try{switch(f){case "actionType":D(c,1,W[a[e]]);break;case "clientActionNonce":D(c,2,a[e]);break;case "clientScreenNonce":D(c,4,a[e]);break;case "loadType":D(c,3,a[e]);break;case "isPrewarmedLaunch":D(c,92,a[e]);break;case "isFirstInstall":D(c,55,a[e]);break;case "networkType":D(c,
5,Rr[a[e]]);break;case "connectionType":D(c,26,X[a[e]]);break;case "detailedConnectionType":D(c,27,Y[a[e]]);break;case "isVisible":D(c,6,a[e]);break;case "playerType":D(c,7,Sr[a[e]]);break;case "clientPlaybackNonce":D(c,8,a[e]);break;case "adClientPlaybackNonce":D(c,28,a[e]);break;case "previousCpn":D(c,77,a[e]);break;case "targetCpn":D(c,76,a[e]);break;case "isMonetized":D(c,9,a[e]);break;case "isPrerollAllowed":D(c,16,a[e]);break;case "isPrerollShown":D(c,17,a[e]);break;case "adType":D(c,12,a[e]);
break;case "adTypesAllowed":D(c,36,a[e]);break;case "adNetworks":D(c,37,a[e]);break;case "previousAction":D(c,13,W[a[e]]);break;case "isRedSubscriber":D(c,14,a[e]);break;case "serverTimeMs":D(c,15,a[e]);break;case "videoId":c.setVideoId(a[e]);break;case "adVideoId":D(c,20,a[e]);break;case "targetVideoId":D(c,78,a[e]);break;case "adBreakType":D(c,21,Tr[a[e]]);break;case "isNavigation":D(c,25,a[e]);break;case "viewportHeight":D(c,29,a[e]);break;case "viewportWidth":D(c,30,a[e]);break;case "screenHeight":D(c,
84,a[e]);break;case "screenWidth":D(c,85,a[e]);break;case "browseId":D(c,31,a[e]);break;case "isCacheHit":D(c,32,a[e]);break;case "httpProtocol":D(c,33,a[e]);break;case "transportProtocol":D(c,34,a[e]);break;case "searchQuery":D(c,41,a[e]);break;case "isContinuation":D(c,42,a[e]);break;case "availableProcessors":D(c,43,a[e]);break;case "sdk":D(c,44,a[e]);break;case "isLocalStream":D(c,45,a[e]);break;case "navigationRequestedSameUrl":D(c,64,a[e]);break;case "shellStartupDurationMs":D(c,70,a[e]);break;
case "appInstallDataAgeMs":D(c,73,a[e]);break;case "latencyActionError":D(c,71,Ur[a[e]]);break;case "actionStep":D(c,79,a[e]);break;case "jsHeapSizeLimit":D(c,80,a[e]);break;case "totalJsHeapSize":D(c,81,a[e]);break;case "usedJsHeapSize":D(c,82,a[e]);break;case "sourceVideoDurationMs":D(c,90,a[e]);break;case "adPrebufferedTimeSecs":D(c,39,a[e]);break;case "isLivestream":D(c,47,a[e]);break;case "liveStreamMode":D(c,91,Vr[a[e]]);break;case "adCpn2":D(c,48,a[e]);break;case "adDaiDriftMillis":D(c,49,
a[e]);break;case "videoStreamType":D(c,53,Wr[a[e]]);break;case "playbackRequiresTap":D(c,56,a[e]);break;case "performanceNavigationTiming":D(c,67,a[e]);break;case "transactionType":D(c,74,Xr[a[e]]);break;case "playerRotationType":D(c,101,Yr[a[e]]);break;case "allowedPreroll":D(c,10,a[e]);break;case "shownPreroll":D(c,11,a[e]);break;case "getHomeRequestId":D(c,57,a[e]);break;case "getSearchRequestId":D(c,60,a[e]);break;case "getPlayerRequestId":D(c,61,a[e]);break;case "getWatchNextRequestId":D(c,62,
a[e]);break;case "getBrowseRequestId":D(c,63,a[e]);break;case "getLibraryRequestId":D(c,66,a[e]);break;default:Zr.includes(f)&&ii(new Q("Codegen laipb translator asked to translate message field",""+f))}}catch(g){ii(Error("Codegen laipb translator failed to set "+f))}}hs(c,b)}}
function hs(a,b){var c=Br(b);c.jspbInfos||(c.jspbInfos=[]);c.jspbInfos.push(a);Ir(b||"").jspbInfo.push(a);c=Dr(b);b=zr(b).cttAuthInfo;bs().jspbInfo(a,c,b)}
function Z(a,b,c){if(!b&&"_"!==a[0]){var d=a;T.mark&&(0==d.lastIndexOf("mark_",0)||(d="mark_"+d),c&&(d+=" ("+c+")"),T.mark(d))}Ir(c||"").tick[a]=b||P();d=Br(c);d.gelTicks&&(d.gelTicks[a]=!0);d=vr(c);var e=b||P();d[a]=e;e=Dr(c);var f=zr(c).cttAuthInfo;if("_start"===a){var g=bs();cs(g,"baseline_"+e)||(b={timestamp:b,cttAuthInfo:f},M("web_csi_via_jspb")?(f=new th,D(f,1,e),e=new Ch,od(e,6,Dh,f),Ep(e,b)):ok("latencyActionBaselined",{clientActionNonce:e},b))}else bs().tick(a,e,b,f);Er(c);return d[a]}
function is(){var a=Dr(void 0);requestAnimationFrame(function(){setTimeout(function(){a===Dr(void 0)&&Z("ol",void 0,void 0)},0)})}
function js(){var a=document;if("visibilityState"in a)a=a.visibilityState;else{var b=xn+"VisibilityState";a=b in a?a[b]:void 0}switch(a){case "hidden":return 0;case "visible":return 1;case "prerender":return 2;case "unloaded":return 3;default:return-1}}
function es(){function a(f){var g=wr(),h=yr();h&&(Z("srt",g.responseStart),1!==f.prerender&&Z("_start",h,void 0));f=Gr();0<f&&Z("fpt",f);f=wr();f.isPerformanceNavigationTiming&&fs({performanceNavigationTiming:!0},void 0);Z("nreqs",f.requestStart,void 0);Z("nress",f.responseStart,void 0);Z("nrese",f.responseEnd,void 0);0<f.redirectEnd-f.redirectStart&&(Z("nrs",f.redirectStart,void 0),Z("nre",f.redirectEnd,void 0));0<f.domainLookupEnd-f.domainLookupStart&&(Z("ndnss",f.domainLookupStart,void 0),Z("ndnse",
f.domainLookupEnd,void 0));0<f.connectEnd-f.connectStart&&(Z("ntcps",f.connectStart,void 0),Z("ntcpe",f.connectEnd,void 0));f.secureConnectionStart>=yr()&&0<f.connectEnd-f.secureConnectionStart&&(Z("nstcps",f.secureConnectionStart,void 0),Z("ntcpe",f.connectEnd,void 0));T&&"getEntriesByType"in T&&ks()}
var b=A("TIMING_INFO",{});if(M("web_csi_via_jspb")){b=ls(b);hs(b);b=new vh;D(b,25,!0);D(b,1,W[Pr(A("TIMING_ACTION",void 0))]);var c=A("PREVIOUS_ACTION",void 0);c&&D(b,13,W[Pr(c)]);(c=A("CLIENT_PROTOCOL"))&&D(b,33,c);(c=A("CLIENT_TRANSPORT"))&&D(b,34,c);(c=kq())&&"UNDEFINED_CSN"!==c&&D(b,4,c);c=js();1!==c&&-1!==c||D(b,6,!0);c=Ar();D(b,3,"cold");a(c);c=ms();if(0<c.length){c=p(c);for(var d=c.next();!d.done;d=c.next()){d=d.value;var e=new uh;D(e,1,d);pd(b,83,uh,e)}}hs(b)}else{for(c in b)b.hasOwnProperty(c)&&
gs(c,b[c]);b={isNavigation:!0,actionType:Pr(A("TIMING_ACTION",void 0))};if(c=A("PREVIOUS_ACTION",void 0))b.previousAction=Pr(c);if(c=A("CLIENT_PROTOCOL"))b.httpProtocol=c;if(c=A("CLIENT_TRANSPORT"))b.transportProtocol=c;(c=kq())&&"UNDEFINED_CSN"!==c&&(b.clientScreenNonce=c);c=js();if(1===c||-1===c)b.isVisible=!0;c=Ar();b.loadType="cold";a(c);c=ms();if(0<c.length)for(b.resourceInfo=[],c=p(c),d=c.next();!d.done;d=c.next())b.resourceInfo.push({resourceCache:d.value});fs(b)}}
function ls(a){var b=new vh;a=p(Object.entries(a));for(var c=a.next();!c.done;c=a.next()){var d=p(c.value);c=d.next().value;d=d.next().value;switch(c){case "GetBrowse_rid":var e=new yh;D(e,1,c);D(e,2,String(d));xh(b,e);break;case "GetGuide_rid":e=new yh;D(e,1,c);D(e,2,String(d));xh(b,e);break;case "GetHome_rid":e=new yh;D(e,1,c);D(e,2,String(d));xh(b,e);break;case "GetPlayer_rid":e=new yh;D(e,1,c);D(e,2,String(d));xh(b,e);break;case "GetSearch_rid":e=new yh;D(e,1,c);D(e,2,String(d));xh(b,e);break;
case "GetSettings_rid":e=new yh;D(e,1,c);D(e,2,String(d));xh(b,e);break;case "GetTrending_rid":e=new yh;D(e,1,c);D(e,2,String(d));xh(b,e);break;case "GetWatchNext_rid":e=new yh;D(e,1,c);D(e,2,String(d));xh(b,e);break;case "yt_red":D(b,14,!!d);break;case "yt_ad":D(b,9,!!d)}}return b}
function ns(a,b){a=document.querySelector(a);if(!a)return!1;var c="",d=a.nodeName;"SCRIPT"===d?(c=a.src,c||(c=a.getAttribute("data-timing-href"))&&(c=window.location.protocol+c)):"LINK"===d&&(c=a.href);Zb()&&a.setAttribute("nonce",Zb());return c?(a=T.getEntriesByName(c))&&a[0]&&(a=a[0],c=yr(),Z("rsf_"+b,c+Math.round(a.fetchStart)),Z("rse_"+b,c+Math.round(a.responseEnd)),void 0!==a.transferSize&&0===a.transferSize)?!0:!1:!1}
function ms(){var a=[];if(document.querySelector&&T&&T.getEntriesByName)for(var b in tr)if(tr.hasOwnProperty(b)){var c=tr[b];ns(b,c)&&a.push(c)}return a}
function ks(){var a=window.location.protocol,b=T.getEntriesByType("resource");b=hb(b,function(c){return 0===c.name.indexOf(a+"//fonts.gstatic.com/s/")});
(b=jb(b,function(c,d){return d.duration>c.duration?d:c},{duration:0}))&&0<b.startTime&&0<b.responseEnd&&(Z("wffs",xr(b.startTime)),Z("wffe",xr(b.responseEnd)))}
var os=window;os.ytcsi&&(os.ytcsi.info=gs,os.ytcsi.tick=Z);var ps=["consistency","mss","client_location","entities","store"];function qs(a,b,c,d){this.o=a;this.J=b;this.l=c;this.j=d;this.i=void 0;this.h=new Map;a.za||(a.za={});a.za=Object.assign({},ir,a.za)}
function rs(a,b,c,d){if(void 0!==qs.h){if(d=qs.h,a=[a!==d.o,b!==d.J,c!==d.l,!1,!1,void 0!==d.i],a.some(function(e){return e}))throw new Q("InnerTubeTransportService is already initialized",a);
}else qs.h=new qs(a,b,c,d)}
function ss(a){var b={signalServiceEndpoint:{signal:"GET_DATASYNC_IDS"}};var c=void 0===c?Rq:c;var d=$q(b,a.o);if(!d)return dg(new Q("Error: No request builder found for command.",b));var e=d.o(b,void 0,c);return e?new Zf(function(f){var g,h,k;return w(function(m){if(1==m.h){h="cors"===(null==(g=e.ra)?void 0:g.mode)?"cors":void 0;if(a.l.zc){var q=e.config,u;q=null==q?void 0:null==(u=q.Ga)?void 0:u.sessionIndex;u=Iq({sessionIndex:q});k=Object.assign({},ts(h),u);return m.s(2)}return t(m,us(e.config,
h),3)}2!=m.h&&(k=m.i);f(vs(a,e,k));m.h=0})}):dg(new Q("Error: Failed to build request for command.",b))}
function vs(a,b,c){var d,e,f,g,h,k,m,q,u,C,v,E,F,H,R,O,S,ka;return w(function(N){switch(N.h){case 1:N.s(2);break;case 3:if((d=N.i)&&!d.isExpired())return N.return(Promise.resolve(d.h()));case 2:if((f=null==(e=b.config)?void 0:e.Xo)&&a.h.has(f)&&M("web_memoize_inflight_requests"))return N.return(a.h.get(f));if(null==(g=b)?0:null==(h=g.ba)?0:h.context)for(k=p([]),m=k.next();!m.done;m=k.next())q=m.value,q.Vo(b.ba.context);if(null==(u=a.i)?0:u.l(b.input,b.ba))return N.return(a.i.j(b.input,b.ba));C=JSON.stringify(b.ba);
b.ra=Object.assign({},b.ra,{headers:c});v=Object.assign({},b.ra);"POST"===b.ra.method&&(v=Object.assign({},v,{body:C}));(null==(E=b.config)?0:E.kc)&&Z(b.config.kc);F=a.J.fetch(b.input,v,b.config);f&&a.h.set(f,F);return t(N,F,4);case 4:H=N.i;f&&a.h.has(f)&&a.h.delete(f);(null==(R=b.config)?0:R.lc)&&Z(b.config.lc);if(H||null==(O=a.i)||!O.h(b.input,b.ba)){N.s(5);break}return t(N,a.i.i(b.input,b.ba),6);case 6:H=N.i;case 5:if(H&&a.j)for(S=p(ps),m=S.next();!m.done;m=S.next())ka=m.value,a.j[ka]&&a.j[ka].handleResponse(H,
b);return N.return(H)}})}
function us(a,b){var c,d,e,f;return w(function(g){if(1==g.h){e=null==(c=a)?void 0:null==(d=c.Ga)?void 0:d.sessionIndex;var h=Iq({sessionIndex:e});if(!(h instanceof Zf)){var k=new Zf(Ma);$f(k,2,h);h=k}return t(g,h,2)}f=g.i;return g.return(Promise.resolve(Object.assign({},ts(b),f)))})}
function ts(a){var b={"Content-Type":"application/json"};M("enable_web_eom_visitor_data")&&A("EOM_VISITOR_DATA")?b["X-Goog-EOM-Visitor-Id"]=A("EOM_VISITOR_DATA"):A("VISITOR_DATA")&&(b["X-Goog-Visitor-Id"]=A("VISITOR_DATA"));"cors"!==a&&((a=A("INNERTUBE_CONTEXT_CLIENT_NAME"))&&(b["X-Youtube-Client-Name"]=a),(a=A("INNERTUBE_CONTEXT_CLIENT_VERSION"))&&(b["X-Youtube-Client-Version"]=a),(a=A("CHROME_CONNECTED_HEADER"))&&(b["X-Youtube-Chrome-Connected"]=a),M("forward_domain_admin_state_on_embeds")&&(a=
A("DOMAIN_ADMIN_STATE"))&&(b["X-Youtube-Domain-Admin-State"]=a));return b}
;var ws=["share/get_web_player_share_panel"],xs=["feedback"],ys=["notification/modify_channel_preference"],zs=["browse/edit_playlist"],As=["subscription/subscribe"],Bs=["subscription/unsubscribe"];function Cs(){}
r(Cs,fr);Cs.prototype.j=function(){return As};
Cs.prototype.h=function(a){return a.subscribeEndpoint};
Cs.prototype.i=function(a,b,c){c=void 0===c?{}:c;b.channelIds&&(a.channelIds=b.channelIds);b.siloName&&(a.siloName=b.siloName);b.params&&(a.params=b.params);c.botguardResponse&&(a.botguardResponse=c.botguardResponse);c.feature&&(a.clientFeature=c.feature)};
da.Object.defineProperties(Cs.prototype,{l:{configurable:!0,enumerable:!0,get:function(){return!0}}});function Ds(){}
r(Ds,fr);Ds.prototype.j=function(){return Bs};
Ds.prototype.h=function(a){return a.unsubscribeEndpoint};
Ds.prototype.i=function(a,b){b.channelIds&&(a.channelIds=b.channelIds);b.siloName&&(a.siloName=b.siloName);b.params&&(a.params=b.params)};
da.Object.defineProperties(Ds.prototype,{l:{configurable:!0,enumerable:!0,get:function(){return!0}}});function Es(){}
r(Es,fr);Es.prototype.j=function(){return xs};
Es.prototype.h=function(a){return a.feedbackEndpoint};
Es.prototype.i=function(a,b,c){a.feedbackTokens=[];b.feedbackToken&&a.feedbackTokens.push(b.feedbackToken);if(b=b.cpn||c.cpn)a.feedbackContext={cpn:b};a.isFeedbackTokenUnencrypted=!!c.is_feedback_token_unencrypted;a.shouldMerge=!1;c.extra_feedback_tokens&&(a.shouldMerge=!0,a.feedbackTokens=a.feedbackTokens.concat(c.extra_feedback_tokens))};
da.Object.defineProperties(Es.prototype,{l:{configurable:!0,enumerable:!0,get:function(){return!0}}});function Fs(){}
r(Fs,fr);Fs.prototype.j=function(){return ys};
Fs.prototype.h=function(a){return a.modifyChannelNotificationPreferenceEndpoint};
Fs.prototype.i=function(a,b){b.params&&(a.params=b.params);b.secondaryParams&&(a.secondaryParams=b.secondaryParams)};function Gs(){}
r(Gs,fr);Gs.prototype.j=function(){return zs};
Gs.prototype.h=function(a){return a.playlistEditEndpoint};
Gs.prototype.i=function(a,b){b.actions&&(a.actions=b.actions);b.params&&(a.params=b.params);b.playlistId&&(a.playlistId=b.playlistId)};function Hs(){}
r(Hs,fr);Hs.prototype.j=function(){return ws};
Hs.prototype.h=function(a){return a.webPlayerShareEntityServiceEndpoint};
Hs.prototype.i=function(a,b,c){c=void 0===c?{}:c;b.serializedShareEntity&&(a.serializedSharedEntity=b.serializedShareEntity);c.includeListId&&(a.includeListId=!0)};var Mq=new Kq("NETWORK_SLI_TOKEN");function Is(a){this.h=a}
Is.prototype.fetch=function(a,b){var c=this,d,e;return w(function(f){c.h&&(d=cc(dc(5,pc(a)))||"/UNKNOWN_PATH",c.h.start(d));e=new window.Request(a,b);return M("web_fetch_promise_cleanup_killswitch")?f.return(Promise.resolve(fetch(e).then(function(g){return c.handleResponse(g)}).catch(function(g){Tp(g)}))):f.return(fetch(e).then(function(g){return c.handleResponse(g)}).catch(function(g){Tp(g)}))})};
Is.prototype.handleResponse=function(a){var b=a.text().then(function(c){return JSON.parse(c.replace(")]}'",""))});
a.redirected||a.ok?this.h&&this.h.success():(this.h&&this.h.failure(),b=b.then(function(c){Tp(new Q("Error: API fetch failed",a.status,a.url,c));return Object.assign({},c,{errorMetadata:{status:a.status}})}));
return b};
Is[Jq]=[new Lq];var Js=new Kq("NETWORK_MANAGER_TOKEN");var Ks;function Ls(a){Vl.call(this,1,arguments);this.csn=a}
r(Ls,Vl);var dm=new Wl("screen-created",Ls),Ms=[],Os=Ns,Ps=0;function Qs(a,b,c,d,e,f,g){function h(){Tp(new Q("newScreen() parent element does not have a VE - rootVe",b))}
var k=Os();f=new dq({veType:b,youtubeData:f,jspbYoutubeData:void 0});e={cttAuthInfo:e,X:k};if(M("il_via_jspb")){var m=new jh;m.S(k);kh(m,f.getAsJspb());c&&c.visualElement?(f=new lh,c.clientScreenNonce&&D(f,2,c.clientScreenNonce),mh(f,c.visualElement.getAsJspb()),g&&D(f,4,Eh[g]),I(m,5,f)):c&&h();d&&D(m,3,d);Jp(m,e,a)}else f={csn:k,pageVe:f.getAsJson()},c&&c.visualElement?(f.implicitGesture={parentCsn:c.clientScreenNonce,gesturedVe:c.visualElement.getAsJson()},g&&(f.implicitGesture.gestureType=g)):
c&&h(),d&&(f.cloneCsn=d),a?op("screenCreated",f,a,e):ok("screenCreated",f,e);am(dm,new Ls(k));return k}
function Rs(a,b,c,d){var e=d.filter(function(k){k.csn!==b?(k.csn=b,k=!0):k=!1;return k}),f={cttAuthInfo:mq(b),
X:b};d=p(d);for(var g=d.next();!g.done;g=d.next())g=g.value.getAsJson(),(qb(g)||!g.trackingParams&&!g.veType)&&Tp(Error("Child VE logged with no data"));if(M("il_via_jspb")){var h=new nh;h.S(b);ph(h,c.getAsJspb());ib(e,function(k){k=k.getAsJspb();pd(h,3,hh,k)});
"UNDEFINED_CSN"==b?Ss("visualElementAttached",h,f):Kp(h,f,a)}else c={csn:b,parentVe:c.getAsJson(),childVes:ib(e,function(k){return k.getAsJson()})},"UNDEFINED_CSN"==b?Ss("visualElementAttached",c,f):a?op("visualElementAttached",c,a,f):ok("visualElementAttached",c,f)}
function Ns(){for(var a=Math.random()+"",b=[],c=0,d=0;d<a.length;d++){var e=a.charCodeAt(d);255<e&&(b[c++]=e&255,e>>=8);b[c++]=e}return Mc(b,3)}
function Ss(a,b,c){Ms.push({payloadName:a,payload:b,options:c});Ps||(Ps=em())}
function fm(a){if(Ms){for(var b=p(Ms),c=b.next();!c.done;c=b.next())if(c=c.value,c.payload)if(M("il_via_jspb"))switch(c.payload.S(a.csn),c.payloadName){case "screenCreated":Jp(c.payload,c.options);break;case "visualElementAttached":Kp(c.payload,c.options);break;case "visualElementShown":Fp(c.payload,c.options);break;case "visualElementHidden":Gp(c.payload,c.options);break;case "visualElementGestured":Hp(c.payload,c.options);break;case "visualElementStateChanged":Ip(c.payload,c.options);break;default:Tp(new Q("flushQueue unable to map payloadName to JSPB setter"))}else c.payload.csn=
a.csn,op(c.payloadName,c.payload,null,c.options);Ms.length=0}Ps=0}
;function Ts(){this.i=new Set;this.h=new Set;this.j=new Map}
Ts.prototype.clear=function(){this.i.clear();this.h.clear();this.j.clear()};
Na(Ts);function Us(){this.o=[];this.C=[];this.h=[];this.l=[];this.m=[];this.i=new Set;this.u=new Map}
function Vs(a,b,c){c=void 0===c?0:c;b.then(function(d){a.i.has(c)&&a.j&&a.j();var e=kq(c),f=iq(c);if(e&&f){var g;(null==d?0:null==(g=d.response)?0:g.trackingParams)&&Rs(a.client,e,f,[eq(d.response.trackingParams)]);var h;(null==d?0:null==(h=d.playerResponse)?0:h.trackingParams)&&Rs(a.client,e,f,[eq(d.playerResponse.trackingParams)])}})}
function Ws(a,b,c,d){d=void 0===d?0:d;if(a.i.has(d))a.o.push([b,c]);else{var e=kq(d);c=c||iq(d);e&&c&&Rs(a.client,e,c,[b])}}
Us.prototype.clickCommand=function(a,b,c){var d=a.clickTrackingParams;c=void 0===c?0:c;if(d)if(c=kq(void 0===c?0:c)){a=this.client;var e=eq(d);var f="INTERACTION_LOGGING_GESTURE_TYPE_GENERIC_CLICK";d={cttAuthInfo:mq(c),X:c};if(M("il_via_jspb")){var g=new qh;g.S(c);e=e.getAsJspb();I(g,2,e);D(g,4,Eh[f]);b&&I(g,3,void 0);"UNDEFINED_CSN"==c?Ss("visualElementGestured",g,d):Hp(g,d,a)}else f={csn:c,ve:e.getAsJson(),gestureType:f},b&&(f.clientData=b),"UNDEFINED_CSN"==c?Ss("visualElementGestured",f,d):a?op("visualElementGestured",
f,a,d):ok("visualElementGestured",f,d);b=!0}else b=!1;else b=!1;return b};
function Xs(a,b,c){c=void 0===c?{}:c;a.i.add(c.layer||0);a.j=function(){Ys(a,b,c);var f=iq(c.layer);if(f){for(var g=p(a.o),h=g.next();!h.done;h=g.next())h=h.value,Ws(a,h[0],h[1]||f,c.layer);f=p(a.C);for(g=f.next();!g.done;g=f.next()){var k=g.value;g=void 0;g=void 0===g?0:g;h=kq(g);var m=k[0]||iq(g);if(h&&m){g=a.client;var q=k[1];k={cttAuthInfo:mq(h),X:h};M("il_via_jspb")?(q=new sh,q.S(h),m=m.getAsJspb(),I(q,2,m),"UNDEFINED_CSN"==h?Ss("visualElementStateChanged",q,k):Ip(q,k,g)):(m={csn:h,ve:m.getAsJson(),
clientData:q},"UNDEFINED_CSN"==h?Ss("visualElementStateChanged",m,k):g?op("visualElementStateChanged",m,g,k):ok("visualElementStateChanged",m,k))}}}};
kq(c.layer)||a.j();if(c.rb)for(var d=p(c.rb),e=d.next();!e.done;e=d.next())Vs(a,e.value,c.layer);else Sp(Error("Delayed screen needs a data promise."))}
function Ys(a,b,c){c=void 0===c?{}:c;c.layer||(c.layer=0);var d=void 0!==c.ec?c.ec:c.layer;var e=kq(d);d=iq(d);var f;d&&(void 0!==c.parentCsn?f={clientScreenNonce:c.parentCsn,visualElement:d}:e&&"UNDEFINED_CSN"!==e&&(f={clientScreenNonce:e,visualElement:d}));var g,h=A("EVENT_ID");"UNDEFINED_CSN"===e&&h&&(g={servletData:{serializedServletEventId:h}});try{var k=Qs(a.client,b,f,c.qb,c.cttAuthInfo,g,c.So)}catch(m){Vp(m,{Yo:b,rootVe:d,parentVisualElement:void 0,Po:e,Uo:f,qb:c.qb});Sp(m);return}nq(k,b,
c.layer,c.cttAuthInfo);if(b=e&&"UNDEFINED_CSN"!==e&&d){a:{b=p(Object.values(cq));for(f=b.next();!f.done;f=b.next())if(kq(f.value)===e){b=!0;break a}b=!1}b=!b}b&&(b=a.client,g=!0,h=(g=void 0===g?!1:g)?16:8,f={cttAuthInfo:mq(e),X:e,tb:g},M("il_via_jspb")?(h=new rh,h.S(e),d=d.getAsJspb(),I(h,2,d),D(h,4,g?16:8),"UNDEFINED_CSN"==e?Ss("visualElementHidden",h,f):Gp(h,f,b)):(d={csn:e,ve:d.getAsJson(),eventType:h},"UNDEFINED_CSN"==e?Ss("visualElementHidden",d,f):b?op("visualElementHidden",d,b,f):ok("visualElementHidden",
d,f)));a.h[a.h.length-1]&&!a.h[a.h.length-1].csn&&(a.h[a.h.length-1].csn=k||"");fs({clientScreenNonce:k});Ts.getInstance().clear();d=iq(c.layer);e&&"UNDEFINED_CSN"!==e&&d&&(M("web_mark_root_visible")||M("music_web_mark_root_visible"))&&(e=k,k={cttAuthInfo:mq(e),X:e},M("il_via_jspb")?(b=new rh,b.S(e),f=d.getAsJspb(),I(b,2,f),D(b,4,1),"UNDEFINED_CSN"==e?Ss("visualElementShown",b,k):Fp(b,k,void 0)):(b={csn:e,ve:d.getAsJson(),eventType:1},"UNDEFINED_CSN"==e?Ss("visualElementShown",b,k):ok("visualElementShown",
b,k)));a.i.delete(c.layer||0);a.j=void 0;e=p(a.u);for(k=e.next();!k.done;k=e.next())b=p(k.value),k=b.next().value,b=b.next().value,b.has(c.layer)&&d&&Ws(a,k,d,c.layer);for(c=0;c<a.l.length;c++){e=a.l[c];try{e()}catch(m){Sp(m)}}for(c=a.l.length=0;c<a.m.length;c++){e=a.m[c];try{e()}catch(m){Sp(m)}}}
;function Zs(){var a,b;return w(function(c){if(1==c.h)return a=qs.h,a?t(c,ss(a),2):(Tp(Error("InnertubeTransportService unavailable in fetchDatasyncIds")),c.return(void 0));if(b=c.i)return b.errorMetadata?(Sp(Error("Datasync IDs fetch responded with "+b.errorMetadata.code+": "+b.error)),c.return(void 0)):c.return(b.Qo);Tp(Error("Network request to get Datasync IDs failed."));return c.return(void 0)})}
;var $s=x.caches,at;function bt(a){var b=a.indexOf(":");return-1===b?{Cb:a}:{Cb:a.substring(0,b),datasyncId:a.substring(b+1)}}
function ct(){return w(function(a){if(void 0!==at)return a.return(at);at=new Promise(function(b){var c;return w(function(d){switch(d.h){case 1:return wa(d,2),t(d,$s.open("test-only"),4);case 4:return t(d,$s.delete("test-only"),5);case 5:xa(d,3);break;case 2:if(c=ya(d),c instanceof Error&&"SecurityError"===c.name)return b(!1),d.return();case 3:b("caches"in window),d.h=0}})});
return a.return(at)})}
function dt(a){var b,c,d,e,f,g,h;w(function(k){if(1==k.h)return t(k,ct(),2);if(3!=k.h){if(!k.i)return k.return(!1);b=[];return t(k,$s.keys(),3)}c=k.i;d=p(c);for(e=d.next();!e.done;e=d.next())f=e.value,g=bt(f),h=g.datasyncId,!h||a.includes(h)||b.push($s.delete(f));return k.return(Promise.all(b).then(function(m){return m.some(function(q){return q})}))})}
function et(){var a,b,c,d,e,f,g;return w(function(h){if(1==h.h)return t(h,ct(),2);if(3!=h.h){if(!h.i)return h.return(!1);a=sk("cache contains other");return t(h,$s.keys(),3)}b=h.i;c=p(b);for(d=c.next();!d.done;d=c.next())if(e=d.value,f=bt(e),(g=f.datasyncId)&&g!==a)return h.return(!0);return h.return(!1)})}
;function ft(){try{return!!self.localStorage}catch(a){return!1}}
;function gt(a){a=a.match(/(.*)::.*::.*/);if(null!==a)return a[1]}
function ht(a){if(ft()){var b=Object.keys(window.localStorage);b=p(b);for(var c=b.next();!c.done;c=b.next()){c=c.value;var d=gt(c);void 0===d||a.includes(d)||self.localStorage.removeItem(c)}}}
function jt(){if(!ft())return!1;var a=sk(),b=Object.keys(window.localStorage);b=p(b);for(var c=b.next();!c.done;c=b.next())if(c=gt(c.value),void 0!==c&&c!==a)return!0;return!1}
;function kt(){Zs().then(function(a){a&&(Cl(a),dt(a),ht(a))})}
function lt(){var a=new Qm;bf.N(function(){var b,c,d,e;return w(function(f){switch(f.h){case 1:if(M("ytidb_clear_optimizations_killswitch")){f.s(2);break}b=sk("clear");if(b.startsWith("V")){var g=[b];Cl(g);dt(g);ht(g);return f.return()}c=jt();return t(f,et(),3);case 3:return d=f.i,t(f,Dl(),4);case 4:if(e=f.i,!c&&!d&&!e)return f.return();case 2:a.H()?kt():a.l.add("publicytnetworkstatus-online",kt,!0,void 0,void 0),f.h=0}})})}
;function mt(a){a&&(a.dataset?a.dataset[nt("loaded")]="true":a.setAttribute("data-loaded","true"))}
function ot(a,b){return a?a.dataset?a.dataset[nt(b)]:a.getAttribute("data-"+b):null}
var pt={};function nt(a){return pt[a]||(pt[a]=String(a).replace(/\-([a-z])/g,function(b,c){return c.toUpperCase()}))}
;var qt=/\.vflset|-vfl[a-zA-Z0-9_+=-]+/,rt=/-[a-zA-Z]{2,3}_[a-zA-Z]{2,3}(?=(\/|$))/;function st(a,b,c){c=void 0===c?null:c;if(window.spf&&spf.script){c="";if(a){var d=a.indexOf("jsbin/"),e=a.lastIndexOf(".js"),f=d+6;-1<d&&-1<e&&e>f&&(c=a.substring(f,e),c=c.replace(qt,""),c=c.replace(rt,""),c=c.replace("debug-",""),c=c.replace("tracing-",""))}spf.script.load(a,c,b)}else tt(a,b,c)}
function tt(a,b,c){c=void 0===c?null:c;var d=ut(a),e=document.getElementById(d),f=e&&ot(e,"loaded"),g=e&&!f;f?b&&b():(b&&(f=Rn(d,b),b=""+Sa(b),vt[b]=f),g||(e=wt(a,d,function(){ot(e,"loaded")||(mt(e),Un(d),Ci(Ya(lo,d),0))},c)))}
function wt(a,b,c,d){d=void 0===d?null:d;var e=Md("SCRIPT");e.id=b;e.onload=function(){c&&setTimeout(c,0)};
e.onreadystatechange=function(){switch(e.readyState){case "loaded":case "complete":e.onload()}};
d&&e.setAttribute("nonce",d);Id(e,Of(a));a=document.getElementsByTagName("head")[0]||document.body;a.insertBefore(e,a.firstChild);return e}
function xt(a){a=ut(a);var b=document.getElementById(a);b&&(lo(a),b.parentNode.removeChild(b))}
function zt(a,b){a&&b&&(a=""+Sa(b),(a=vt[a])&&Tn(a))}
function ut(a){var b=document.createElement("a");Wb(b,a);a=b.href.replace(/^[a-zA-Z]+:\/\//,"//");return"js-"+ac(a)}
var vt={};var At=[],Bt=!1;function Ct(){if(!M("disable_biscotti_fetch_for_ad_blocker_detection")&&!M("disable_biscotti_fetch_entirely_for_all_web_clients")&&yq()&&"1"!=ub()){var a=function(){Bt=!0;"google_ad_status"in window?Zh("DCLKSTAT",1):Zh("DCLKSTAT",2)};
try{st("//static.doubleclick.net/instream/ad_status.js",a)}catch(b){}At.push(bf.N(function(){if(!(Bt||"google_ad_status"in window)){try{zt("//static.doubleclick.net/instream/ad_status.js",a)}catch(b){}Bt=!0;Zh("DCLKSTAT",3)}},5E3))}}
function Dt(){var a=Number(A("DCLKSTAT",0));return isNaN(a)?0:a}
;function Et(){this.state=1;this.h=null}
l=Et.prototype;
l.initialize=function(a,b,c){if(a.program){var d,e=null!=(d=a.interpreterScript)?d:null,f;d=null!=(f=a.interpreterUrl)?f:null;a.interpreterSafeScript&&(e=a.interpreterSafeScript,Eb("From proto message. b/166824318"),e=e.privateDoNotAccessOrElseSafeScriptWrappedValue||"",e=(f=Bb())?f.createScript(e):e,e=(new Gb(e)).toString());a.interpreterSafeUrl&&(d=a.interpreterSafeUrl,Eb("From proto message. b/166824318"),d=Kb(d.privateDoNotAccessOrElseTrustedResourceUrlWrappedValue||"").toString());Ft(this,e,
d,a.program,b,c)}else Tp(Error("Cannot initialize botguard without program"))};
function Ft(a,b,c,d,e,f){var g=void 0===g?"trayride":g;c?(a.state=2,st(c,function(){window[g]?It(a,d,g,e):(a.state=3,xt(c),Tp(new Q("Unable to load Botguard","from "+c)))},f)):b?(f=Md("SCRIPT"),f.textContent=b,f.nonce=Zb(),document.head.appendChild(f),document.head.removeChild(f),window[g]?It(a,d,g,e):(a.state=4,Tp(new Q("Unable to load Botguard from JS")))):Tp(new Q("Unable to load VM; no url or JS provided"))}
l.isInitialized=function(){return!!this.h};
l.getState=function(){return this.state};
function It(a,b,c,d){a.state=5;try{var e=new Bd({program:b,globalName:c});e.wc.then(function(){a.state=6;d&&d(b)});
Jt(a,e)}catch(f){a.state=7,f instanceof Error&&Tp(f)}}
l.invoke=function(a){a=void 0===a?{}:a;if(this.h){var b=this.h;a={pb:a};if(b.i)throw Error("Already disposed");b=b.l([a.pb,a.yc])}else b=null;return b};
l.dispose=function(){Jt(this,null);this.state=8};
function Jt(a,b){pe(a.h);a.h=b}
;var Kt=new Et;function Lt(){return Kt.isInitialized()}
function Mt(a){a=void 0===a?{}:a;return Kt.invoke(a)}
;function Nt(a){var b=this;var c=void 0===c?0:c;var d=void 0===d?dk():d;this.l=c;this.j=d;this.i=new Ad;this.h=a;a={};c=p(this.h.entries());for(d=c.next();!d.done;a={sa:a.sa,Ba:a.Ba},d=c.next()){var e=p(d.value);d=e.next().value;e=e.next().value;a.Ba=d;a.sa=e;d=function(f){return function(){f.sa.eb();b.h[f.Ba].Ra=!0;b.h.every(function(g){return!0===g.Ra})&&b.i.resolve()}}(a);
e=Zj(d,Ot(this,a.sa));this.h[a.Ba]=Object.assign({},a.sa,{eb:d,Na:e})}}
function Pt(a){var b=Array.from(a.h.keys()).sort(function(d,e){return Ot(a,a.h[e])-Ot(a,a.h[d])});
b=p(b);for(var c=b.next();!c.done;c=b.next())c=a.h[c.value],void 0===c.Na||c.Ra||(a.j.U(c.Na),Zj(c.eb,10))}
Nt.prototype.cancel=function(){for(var a=p(this.h),b=a.next();!b.done;b=a.next())b=b.value,void 0===b.Na||b.Ra||this.j.U(b.Na),b.Ra=!0;this.i.resolve()};
function Ot(a,b){var c;return null!=(c=b.priority)?c:a.l}
;function Qt(a){this.state=a;this.plugins=[];this.m=void 0}
Qt.prototype.install=function(){this.plugins.push.apply(this.plugins,fa(Ja.apply(0,arguments)))};
Qt.prototype.transition=function(a,b){var c=this,d=this.C.find(function(f){return f.from===c.state&&f.B===a});
if(d){this.j&&(Pt(this.j),this.j=void 0);this.state=a;d=d.action.bind(this);var e=this.plugins.filter(function(f){return f[a]}).map(function(f){return f[a]});
d(Rt(this,e,this.m),b)}else throw Error("no transition specified from "+this.state+" to "+a);};
function Rt(a,b,c){return function(){var d=Ja.apply(0,arguments),e=b.filter(function(k){var m;return 10===(null!=(m=null!=c?c:k.priority)?m:0)}),f=b.filter(function(k){var m;
return 10!==(null!=(m=null!=c?c:k.priority)?m:0)});
dk();var g={};e=p(e);for(var h=e.next();!h.done;g={Ca:g.Ca},h=e.next())g.Ca=h.value,bk(function(k){return function(){k.Ca.ka.apply(k.Ca,fa(d))}}(g));
f=f.map(function(k){var m;return{eb:function(){k.ka.apply(k,fa(d))},
priority:null!=(m=null!=c?c:k.priority)?m:0}});
f.length&&(a.j=new Nt(f))}}
da.Object.defineProperties(Qt.prototype,{currentState:{configurable:!0,enumerable:!0,get:function(){return this.state}}});function St(a){Qt.call(this,void 0===a?"document_active":a);var b=this;this.m=10;this.h=new Map;this.C=[{from:"document_active",B:"document_disposed_preventable",action:this.u},{from:"document_active",B:"document_disposed",action:this.l},{from:"document_disposed_preventable",B:"document_disposed",action:this.l},{from:"document_disposed_preventable",B:"flush_logs",action:this.o},{from:"document_disposed_preventable",B:"document_active",action:this.i},{from:"document_disposed",B:"flush_logs",action:this.o},
{from:"document_disposed",B:"document_active",action:this.i},{from:"document_disposed",B:"document_disposed",action:function(){}},
{from:"flush_logs",B:"document_active",action:this.i}];window.addEventListener("pagehide",function(c){b.transition("document_disposed",{event:c})});
window.addEventListener("beforeunload",function(c){b.transition("document_disposed_preventable",{event:c})})}
r(St,Qt);St.prototype.u=function(a,b){if(!this.h.get("document_disposed_preventable")){a(null==b?void 0:b.event);var c,d;if((null==b?0:null==(c=b.event)?0:c.defaultPrevented)||(null==b?0:null==(d=b.event)?0:d.returnValue)){b.event.returnValue||(b.event.returnValue=!0);b.event.defaultPrevented||b.event.preventDefault();this.h=new Map;this.transition("document_active");return}}this.h.set("document_disposed_preventable",!0);this.h.get("document_disposed")?this.transition("flush_logs"):this.transition("document_disposed")};
St.prototype.l=function(a,b){this.h.get("document_disposed")?this.transition("document_active"):(a(null==b?void 0:b.event),this.h.set("document_disposed",!0),this.transition("flush_logs"))};
St.prototype.o=function(a,b){a(null==b?void 0:b.event);this.transition("document_active")};
St.prototype.i=function(){this.h=new Map};function Tt(a){Qt.call(this,void 0===a?"document_visibility_unknown":a);var b=this;this.C=[{from:"document_visibility_unknown",B:"document_visible",action:this.i},{from:"document_visibility_unknown",B:"document_hidden",action:this.h},{from:"document_visibility_unknown",B:"document_foregrounded",action:this.o},{from:"document_visibility_unknown",B:"document_backgrounded",action:this.l},{from:"document_visible",B:"document_hidden",action:this.h},{from:"document_visible",B:"document_foregrounded",action:this.o},
{from:"document_visible",B:"document_visible",action:this.i},{from:"document_foregrounded",B:"document_visible",action:this.i},{from:"document_foregrounded",B:"document_hidden",action:this.h},{from:"document_foregrounded",B:"document_foregrounded",action:this.o},{from:"document_hidden",B:"document_visible",action:this.i},{from:"document_hidden",B:"document_backgrounded",action:this.l},{from:"document_hidden",B:"document_hidden",action:this.h},{from:"document_backgrounded",B:"document_hidden",action:this.h},
{from:"document_backgrounded",B:"document_backgrounded",action:this.l},{from:"document_backgrounded",B:"document_visible",action:this.i}];document.addEventListener("visibilitychange",function(c){"visible"===document.visibilityState?b.transition("document_visible",{event:c}):b.transition("document_hidden",{event:c})});
M("visibility_lifecycles_dynamic_backgrounding")&&(window.addEventListener("blur",function(c){b.transition("document_backgrounded",{event:c})}),window.addEventListener("focus",function(c){b.transition("document_foregrounded",{event:c})}))}
r(Tt,Qt);Tt.prototype.i=function(a,b){a(null==b?void 0:b.event);M("visibility_lifecycles_dynamic_backgrounding")&&this.transition("document_foregrounded")};
Tt.prototype.h=function(a,b){a(null==b?void 0:b.event);M("visibility_lifecycles_dynamic_backgrounding")&&this.transition("document_backgrounded")};
Tt.prototype.l=function(a,b){a(null==b?void 0:b.event)};
Tt.prototype.o=function(a,b){a(null==b?void 0:b.event)};function Ut(){this.h=new St;this.i=new Tt}
Ut.prototype.install=function(){var a=Ja.apply(0,arguments);this.h.install.apply(this.h,fa(a));this.i.install.apply(this.i,fa(a))};function Vt(){Ut.call(this);var a={};this.install((a.document_disposed={ka:this.j},a));a={};this.install((a.flush_logs={ka:this.l},a))}
var Wt;r(Vt,Ut);Vt.prototype.l=function(){if(M("web_fp_via_jspb")){var a=new gh,b=kq();b&&a.S(b);b=new Ch;od(b,380,Dh,a);Ep(b,void 0);M("web_fp_via_jspb_and_json")&&ok("finalPayload",{csn:kq()})}else ok("finalPayload",{csn:kq()})};
Vt.prototype.j=function(){Xp(Yp)};function Xt(){}
Xt.getInstance=function(){var a=z("ytglobal.storage_");a||(a=new Xt,y("ytglobal.storage_",a,void 0));return a};
Xt.prototype.estimate=function(){var a,b,c;return w(function(d){a=navigator;return(null==(b=a.storage)?0:b.estimate)?d.return(a.storage.estimate()):(null==(c=a.webkitTemporaryStorage)?0:c.queryUsageAndQuota)?d.return(Yt()):d.return()})};
function Yt(){var a=navigator;return new Promise(function(b,c){var d;null!=(d=a.webkitTemporaryStorage)&&d.queryUsageAndQuota?a.webkitTemporaryStorage.queryUsageAndQuota(function(e,f){b({usage:e,quota:f})},function(e){c(e)}):c(Error("webkitTemporaryStorage is not supported."))})}
y("ytglobal.storageClass_",Xt,void 0);function mk(a,b){var c=this;this.handleError=a;this.h=b;this.i=!1;void 0===self.document||self.addEventListener("beforeunload",function(){c.i=!0});
this.j=Math.random()<=ci("ytidb_transaction_ended_event_rate_limit",.02)}
mk.prototype.logEvent=function(a,b){switch(a){case "IDB_DATA_CORRUPTED":M("idb_data_corrupted_killswitch")||this.h("idbDataCorrupted",b);break;case "IDB_UNEXPECTEDLY_CLOSED":this.h("idbUnexpectedlyClosed",b);break;case "IS_SUPPORTED_COMPLETED":M("idb_is_supported_completed_killswitch")||this.h("idbIsSupportedCompleted",b);break;case "QUOTA_EXCEEDED":Zt(this,b);break;case "TRANSACTION_ENDED":this.j&&this.h("idbTransactionEnded",b);break;case "TRANSACTION_UNEXPECTEDLY_ABORTED":a=Object.assign({},b,
{hasWindowUnloaded:this.i}),this.h("idbTransactionAborted",a)}};
function Zt(a,b){Xt.getInstance().estimate().then(function(c){c=Object.assign({},b,{isSw:void 0===self.document,isIframe:self!==self.top,deviceStorageUsageMbytes:$t(null==c?void 0:c.usage),deviceStorageQuotaMbytes:$t(null==c?void 0:c.quota)});a.h("idbQuotaExceeded",c)})}
function $t(a){return"undefined"===typeof a?"-1":String(Math.ceil(a/1048576))}
;var au=window;
function bu(){var a=au.uaChPolyfill.state;if(0===a.type)ok("clientHintsPolyfillEvent",{clientHintsSupported:!1});else{var b=navigator.userAgent,c=void 0!==a.syntheticUa&&a.syntheticUa===b,d={clientHintsSupported:!0,uaAccessedBeforePolyfill:a.didAccessUaBeforePolyfillAvailable,syntheticUaMatches:c};a.didAccessUaBeforePolyfillAvailable&&(d.uaAccessBeforePolyfillCount=a.uaAccessBeforePolyfillCount,a.firstAccessUaError&&(d.firstUaAccessStack=String(a.firstAccessUaError.stack).replace(/\n/g,""),Sp(a.firstAccessUaError)),
d.polyfillAvailabilityDelayMs=a.polyfillAvailabilityDelay);ok("clientHintsPolyfillEvent",d);c||(b={syntheticUa:a.syntheticUa,ua:b},b.brand=a.data.brands.map(function(e){return'"'+e.brand+'"; v="'+e.version+'"'}),b.mobileness=a.data.mobile,a=a.data.values,a.architecture&&(b.platformArchitecture=a.architecture),a.model&&(b.model=a.model),a.platform&&(b.platformBrand=a.platform),a.platformVersion&&(b.platformVersion=a.platformVersion),a.uaFullVersion&&(b.fullVersion=a.uaFullVersion),ok("clientHintsPolyfillDiagnostics",
b))}}
var cu=!1;function du(){var a;1===(null==(a=au.uaChPolyfill)?void 0:a.state.type)?cu||(au.uaChPolyfill.onReady=du,cu=!0):au.uaChPolyfill&&bu()}
;function eu(a,b,c){K.call(this);var d=this;c=c||A("POST_MESSAGE_ORIGIN",void 0)||window.document.location.protocol+"//"+window.document.location.hostname;this.j=b||null;this.L="*";this.l=c;this.sessionId=null;this.channel="widget";this.M=!!a;this.A=function(e){a:if(!("*"!=d.l&&e.origin!=d.l||d.j&&e.source!=d.j||"string"!==typeof e.data)){try{var f=JSON.parse(e.data)}catch(g){break a}if(!(null==f||d.M&&(d.sessionId&&d.sessionId!=f.id||d.channel&&d.channel!=f.channel))&&f)switch(f.event){case "listening":"null"!=
e.origin&&(d.l=d.L=e.origin);d.j=e.source;d.sessionId=f.id;d.i&&(d.i(),d.i=null);break;case "command":d.m&&(!d.u||0<=fb(d.u,f.func))&&d.m(f.func,f.args,e.origin)}}};
this.u=this.i=this.m=null;window.addEventListener("message",this.A)}
r(eu,K);eu.prototype.sendMessage=function(a,b){if(b=b||this.j){this.sessionId&&(a.id=this.sessionId);this.channel&&(a.channel=this.channel);try{var c=JSON.stringify(a);b.postMessage(c,this.L)}catch(d){ji(d)}}};
eu.prototype.I=function(){window.removeEventListener("message",this.A);K.prototype.I.call(this)};function fu(){this.i=[];this.isReady=!1;this.j={};var a=this.h=new eu(!!A("WIDGET_ID_ENFORCE")),b=this.ic.bind(this);a.m=b;a.u=null;this.h.channel="widget";if(a=A("WIDGET_ID"))this.h.sessionId=a}
l=fu.prototype;l.ic=function(a,b,c){"addEventListener"===a&&b?(a=b[0],this.j[a]||"onReady"===a||(this.addEventListener(a,gu(this,a)),this.j[a]=!0)):this.kb(a,b,c)};
l.kb=function(){};
function gu(a,b){return function(c){return a.sendMessage(b,c)}}
l.addEventListener=function(){};
l.Vb=function(){this.isReady=!0;this.sendMessage("initialDelivery",this.Xa());this.sendMessage("onReady");gb(this.i,this.Ib,this);this.i=[]};
l.Xa=function(){return null};
function hu(a,b){a.sendMessage("infoDelivery",b)}
l.Ib=function(a){this.isReady?this.h.sendMessage(a):this.i.push(a)};
l.sendMessage=function(a,b){this.Ib({event:a,info:void 0===b?null:b})};
l.dispose=function(){this.h=null};function iu(a){return(0===a.search("cue")||0===a.search("load"))&&"loadModule"!==a}
function ju(a,b,c){if("string"===typeof a)return{videoId:a,startSeconds:b,suggestedQuality:c};b=["endSeconds","startSeconds","mediaContentUrl","suggestedQuality","videoId"];c={};for(var d=0;d<b.length;d++){var e=b[d];a[e]&&(c[e]=a[e])}return c}
function ku(a,b,c,d){if(Ra(a)&&!Array.isArray(a)){b="playlist list listType index startSeconds suggestedQuality".split(" ");c={};for(d=0;d<b.length;d++){var e=b[d];a[e]&&(c[e]=a[e])}return c}b={index:b,startSeconds:c,suggestedQuality:d};"string"===typeof a&&16===a.length?b.list="PL"+a:b.playlist=a;return b}
;function lu(a){fu.call(this);this.listeners=[];this.api=a;this.addEventListener("onReady",this.onReady.bind(this));this.addEventListener("onVideoProgress",this.tc.bind(this));this.addEventListener("onVolumeChange",this.uc.bind(this));this.addEventListener("onApiChange",this.mc.bind(this));this.addEventListener("onPlaybackQualityChange",this.pc.bind(this));this.addEventListener("onPlaybackRateChange",this.qc.bind(this));this.addEventListener("onStateChange",this.sc.bind(this));this.addEventListener("onWebglSettingsChanged",
this.vc.bind(this))}
r(lu,fu);l=lu.prototype;
l.kb=function(a,b,c){if(this.api.isExternalMethodAvailable(a,c)){b=b||[];if(0<b.length&&iu(a)){var d=b;if(Ra(d[0])&&!Array.isArray(d[0]))var e=d[0];else switch(e={},a){case "loadVideoById":case "cueVideoById":e=ju(d[0],void 0!==d[1]?Number(d[1]):void 0,d[2]);break;case "loadVideoByUrl":case "cueVideoByUrl":e=d[0];"string"===typeof e&&(e={mediaContentUrl:e,startSeconds:void 0!==d[1]?Number(d[1]):void 0,suggestedQuality:d[2]});b:{if((d=e.mediaContentUrl)&&(d=/\/([ve]|embed)\/([^#?]+)/.exec(d))&&d[2]){d=
d[2];break b}d=null}e.videoId=d;e=ju(e);break;case "loadPlaylist":case "cuePlaylist":e=ku(d[0],d[1],d[2],d[3])}b.length=1;b[0]=e}this.api.handleExternalCall(a,b,c);iu(a)&&hu(this,this.Xa())}};
l.onReady=function(){var a=this.Vb.bind(this);this.h.i=a};
l.addEventListener=function(a,b){this.listeners.push({eventType:a,listener:b});this.api.addEventListener(a,b)};
l.Xa=function(){if(!this.api)return null;var a=this.api.getApiInterface();lb(a,"getVideoData");for(var b={apiInterface:a},c=0,d=a.length;c<d;c++){var e=a[c];if(0===e.search("get")||0===e.search("is")){var f=0;0===e.search("get")?f=3:0===e.search("is")&&(f=2);f=e.charAt(f).toLowerCase()+e.substr(f+1);try{var g=this.api[e]();b[f]=g}catch(h){}}}b.videoData=this.api.getVideoData();b.currentTimeLastUpdated_=Date.now()/1E3;return b};
l.sc=function(a){a={playerState:a,currentTime:this.api.getCurrentTime(),duration:this.api.getDuration(),videoData:this.api.getVideoData(),videoStartBytes:0,videoBytesTotal:this.api.getVideoBytesTotal(),videoLoadedFraction:this.api.getVideoLoadedFraction(),playbackQuality:this.api.getPlaybackQuality(),availableQualityLevels:this.api.getAvailableQualityLevels(),currentTimeLastUpdated_:Date.now()/1E3,playbackRate:this.api.getPlaybackRate(),mediaReferenceTime:this.api.getMediaReferenceTime()};this.api.getVideoUrl&&
(a.videoUrl=this.api.getVideoUrl());this.api.getVideoContentRect&&(a.videoContentRect=this.api.getVideoContentRect());this.api.getProgressState&&(a.progressState=this.api.getProgressState());this.api.getPlaylist&&(a.playlist=this.api.getPlaylist());this.api.getPlaylistIndex&&(a.playlistIndex=this.api.getPlaylistIndex());this.api.getStoryboardFormat&&(a.storyboardFormat=this.api.getStoryboardFormat());hu(this,a)};
l.pc=function(a){hu(this,{playbackQuality:a})};
l.qc=function(a){hu(this,{playbackRate:a})};
l.mc=function(){for(var a=this.api.getOptions(),b={namespaces:a},c=0,d=a.length;c<d;c++){var e=a[c],f=this.api.getOptions(e);b[e]={options:f};for(var g=0,h=f.length;g<h;g++){var k=f[g],m=this.api.getOption(e,k);b[e][k]=m}}this.sendMessage("apiInfoDelivery",b)};
l.uc=function(){hu(this,{muted:this.api.isMuted(),volume:this.api.getVolume()})};
l.tc=function(a){a={currentTime:a,videoBytesLoaded:this.api.getVideoBytesLoaded(),videoLoadedFraction:this.api.getVideoLoadedFraction(),currentTimeLastUpdated_:Date.now()/1E3,playbackRate:this.api.getPlaybackRate(),mediaReferenceTime:this.api.getMediaReferenceTime()};this.api.getProgressState&&(a.progressState=this.api.getProgressState());hu(this,a)};
l.vc=function(){var a={sphericalProperties:this.api.getSphericalProperties()};hu(this,a)};
l.dispose=function(){fu.prototype.dispose.call(this);for(var a=0;a<this.listeners.length;a++){var b=this.listeners[a];this.api.removeEventListener(b.eventType,b.listener)}this.listeners=[]};function mu(a){K.call(this);this.i={};this.started=!1;this.connection=a;this.connection.subscribe("command",this.Eb,this)}
r(mu,K);l=mu.prototype;l.start=function(){this.started||this.h()||(this.started=!0,this.connection.la("RECEIVING"))};
l.la=function(a,b){this.started&&!this.h()&&this.connection.la(a,b)};
l.Eb=function(a,b,c){if(this.started&&!this.h()){var d=b||{};switch(a){case "addEventListener":"string"===typeof d.event&&this.addListener(d.event);break;case "removeEventListener":"string"===typeof d.event&&this.removeListener(d.event);break;default:this.api.isReady()&&this.api.isExternalMethodAvailable(a,c||null)&&(b=nu(a,b||{}),c=this.api.handleExternalCall(a,b,c||null),(c=ou(a,c))&&this.la(a,c))}}};
l.addListener=function(a){if(!(a in this.i)){var b=this.nc.bind(this,a);this.i[a]=b;this.addEventListener(a,b)}};
l.nc=function(a,b){this.started&&!this.h()&&this.connection.la(a,this.Wa(a,b))};
l.Wa=function(a,b){if(null!=b)return{value:b}};
l.removeListener=function(a){a in this.i&&(this.removeEventListener(a,this.i[a]),delete this.i[a])};
l.I=function(){var a=this.connection;a.h()||qg(a.i,"command",this.Eb,this);this.connection=null;for(var b in this.i)this.i.hasOwnProperty(b)&&this.removeListener(b);K.prototype.I.call(this)};function pu(a,b){mu.call(this,b);this.api=a;this.start()}
r(pu,mu);pu.prototype.addEventListener=function(a,b){this.api.addEventListener(a,b)};
pu.prototype.removeEventListener=function(a,b){this.api.removeEventListener(a,b)};
function nu(a,b){switch(a){case "loadVideoById":return a=ju(b),[a];case "cueVideoById":return a=ju(b),[a];case "loadVideoByPlayerVars":return[b];case "cueVideoByPlayerVars":return[b];case "loadPlaylist":return a=ku(b),[a];case "cuePlaylist":return a=ku(b),[a];case "seekTo":return[b.seconds,b.allowSeekAhead];case "playVideoAt":return[b.index];case "setVolume":return[b.volume];case "setPlaybackQuality":return[b.suggestedQuality];case "setPlaybackRate":return[b.suggestedRate];case "setLoop":return[b.loopPlaylists];
case "setShuffle":return[b.shufflePlaylist];case "getOptions":return[b.module];case "getOption":return[b.module,b.option];case "setOption":return[b.module,b.option,b.value];case "handleGlobalKeyDown":return[b.keyCode,b.shiftKey,b.ctrlKey,b.altKey,b.metaKey,b.key,b.code]}return[]}
function ou(a,b){switch(a){case "isMuted":return{muted:b};case "getVolume":return{volume:b};case "getPlaybackRate":return{playbackRate:b};case "getAvailablePlaybackRates":return{availablePlaybackRates:b};case "getVideoLoadedFraction":return{videoLoadedFraction:b};case "getPlayerState":return{playerState:b};case "getCurrentTime":return{currentTime:b};case "getPlaybackQuality":return{playbackQuality:b};case "getAvailableQualityLevels":return{availableQualityLevels:b};case "getDuration":return{duration:b};
case "getVideoUrl":return{videoUrl:b};case "getVideoEmbedCode":return{videoEmbedCode:b};case "getPlaylist":return{playlist:b};case "getPlaylistIndex":return{playlistIndex:b};case "getOptions":return{options:b};case "getOption":return{option:b}}}
pu.prototype.Wa=function(a,b){switch(a){case "onReady":return;case "onStateChange":return{playerState:b};case "onPlaybackQualityChange":return{playbackQuality:b};case "onPlaybackRateChange":return{playbackRate:b};case "onError":return{errorCode:b}}return mu.prototype.Wa.call(this,a,b)};
pu.prototype.I=function(){mu.prototype.I.call(this);delete this.api};function qu(a){a=void 0===a?!1:a;K.call(this);this.i=new L(a);re(this,Ya(pe,this.i))}
$a(qu,K);qu.prototype.subscribe=function(a,b,c){return this.h()?0:this.i.subscribe(a,b,c)};
qu.prototype.l=function(a,b){this.h()||this.i.ja.apply(this.i,arguments)};function ru(a,b,c){qu.call(this);this.j=a;this.destination=b;this.id=c}
r(ru,qu);ru.prototype.la=function(a,b){this.h()||this.j.la(this.destination,this.id,a,b)};
ru.prototype.I=function(){this.destination=this.j=null;qu.prototype.I.call(this)};function su(a,b,c){K.call(this);this.destination=a;this.origin=c;this.i=En(window,"message",this.j.bind(this));this.connection=new ru(this,a,b);re(this,Ya(pe,this.connection))}
r(su,K);su.prototype.la=function(a,b,c,d){this.h()||a!==this.destination||(a={id:b,command:c},d&&(a.data=d),this.destination.postMessage(Sf(a),this.origin))};
su.prototype.j=function(a){var b;if(b=!this.h())if(b=a.origin===this.origin)a:{b=this.destination;do{b:{var c=a.source;do{if(c===b){c=!0;break b}if(c===c.parent)break;c=c.parent}while(null!=c);c=!1}if(c){b=!0;break a}b=b.opener}while(null!=b);b=!1}if(b&&(b=a.data,"string"===typeof b)){try{b=JSON.parse(b)}catch(d){return}b.command&&(c=this.connection,c.h()||c.l("command",b.command,b.data,a.origin))}};
su.prototype.I=function(){Fn(this.i);this.destination=null;K.prototype.I.call(this)};function tu(a){a=a||{};var b={},c={};this.url=a.url||"";this.args=a.args||wb(b);this.assets=a.assets||{};this.attrs=a.attrs||wb(c);this.fallback=a.fallback||null;this.fallbackMessage=a.fallbackMessage||null;this.html5=!!a.html5;this.disable=a.disable||{};this.loaded=!!a.loaded;this.messages=a.messages||{}}
tu.prototype.clone=function(){var a=new tu,b;for(b in this)if(this.hasOwnProperty(b)){var c=this[b];"object"==Pa(c)?a[b]=wb(c):a[b]=c}return a};var uu=/cssbin\/(?:debug-)?([a-zA-Z0-9_-]+?)(?:-2x|-web|-rtl|-vfl|.css)/;function vu(a){a=a||"";if(window.spf){var b=a.match(uu);spf.style.load(a,b?b[1]:"",void 0)}else wu(a)}
function wu(a){var b=xu(a),c=document.getElementById(b),d=c&&ot(c,"loaded");d||c&&!d||(c=yu(a,b,function(){ot(c,"loaded")||(mt(c),Un(b),Ci(Ya(lo,b),0))}))}
function yu(a,b,c){var d=document.createElement("link");d.id=b;d.onload=function(){c&&setTimeout(c,0)};
a=Of(a);Xb(d,a);(document.getElementsByTagName("head")[0]||document.body).appendChild(d);return d}
function xu(a){var b=Md("A");Eb("This URL is never added to the DOM");Wb(b,new Ob(a,Pb));a=b.href.replace(/^[a-zA-Z]+:\/\//,"//");return"css-"+ac(a)}
;function zu(){K.call(this);this.i=[]}
r(zu,K);zu.prototype.I=function(){for(;this.i.length;){var a=this.i.pop();a.target.removeEventListener(a.name,a.ka,void 0)}K.prototype.I.call(this)};function Au(){zu.apply(this,arguments)}
r(Au,zu);function Bu(a,b,c,d){K.call(this);var e=this;this.M=b;this.webPlayerContextConfig=d;this.Ta=!1;this.api={};this.Da=this.u=null;this.T=new L;this.i={};this.fa=this.Ea=this.elementId=this.Ua=this.config=null;this.Y=!1;this.l=this.A=null;this.Fa={};this.Mb=["onReady"];this.lastError=null;this.lb=NaN;this.L={};this.Nb=new Au(this);this.na=0;this.j=this.m=a;re(this,Ya(pe,this.T));Cu(this);Du(this);re(this,Ya(pe,this.Nb));c?this.na=Ci(function(){e.loadNewVideoConfig(c)},0):d&&(Eu(this),Fu(this))}
r(Bu,K);l=Bu.prototype;l.getId=function(){return this.M};
l.loadNewVideoConfig=function(a){if(!this.h()){this.na&&(Di(this.na),this.na=0);var b=a||{};b instanceof tu||(b=new tu(b));this.config=b;this.setConfig(a);Fu(this);this.isReady()&&Gu(this)}};
function Eu(a){var b;a.webPlayerContextConfig?b=a.webPlayerContextConfig.rootElementId:b=a.config.attrs.id;a.elementId=b||a.elementId;"video-player"===a.elementId&&(a.elementId=a.M,a.webPlayerContextConfig?a.webPlayerContextConfig.rootElementId=a.M:a.config.attrs.id=a.M);var c;(null==(c=a.j)?void 0:c.id)===a.elementId&&(a.elementId+="-player",a.webPlayerContextConfig?a.webPlayerContextConfig.rootElementId=a.elementId:a.config.attrs.id=a.elementId)}
l.setConfig=function(a){this.Ua=a;this.config=Hu(a);Eu(this);if(!this.Ea){var b;this.Ea=Iu(this,(null==(b=this.config.args)?void 0:b.jsapicallback)||"onYouTubePlayerReady")}this.config.args?this.config.args.jsapicallback=null:this.config.args={jsapicallback:null};var c;if(null==(c=this.config)?0:c.attrs)a=this.config.attrs,(b=a.width)&&this.j&&(this.j.style.width=Xd(Number(b)||b)),(a=a.height)&&this.j&&(this.j.style.height=Xd(Number(a)||a))};
function Gu(a){if(a.config&&!0!==a.config.loaded)if(a.config.loaded=!0,!a.config.args||"0"!==a.config.args.autoplay&&0!==a.config.args.autoplay&&!1!==a.config.args.autoplay){var b;a.api.loadVideoByPlayerVars(null!=(b=a.config.args)?b:null)}else a.api.cueVideoByPlayerVars(a.config.args)}
function Ju(a){var b=!0,c=Ku(a);c&&a.config&&(a=Lu(a),b=ot(c,"version")===a);return b&&!!z("yt.player.Application.create")}
function Fu(a){if(!a.h()&&!a.Y){var b=Ju(a);if(b&&"html5"===(Ku(a)?"html5":null))a.fa="html5",a.isReady()||Mu(a);else if(Nu(a),a.fa="html5",b&&a.l&&a.m)a.m.appendChild(a.l),Mu(a);else{a.config&&(a.config.loaded=!0);var c=!1;a.A=function(){c=!0;var d=Ou(a,"player_bootstrap_method")?z("yt.player.Application.createAlternate")||z("yt.player.Application.create"):z("yt.player.Application.create");var e=a.config?Hu(a.config):void 0;d&&d(a.m,e,a.webPlayerContextConfig);Mu(a)};
a.Y=!0;b?a.A():(st(Lu(a),a.A),(b=Pu(a))&&vu(b),Qu(a)&&!c&&y("yt.player.Application.create",null,void 0))}}}
function Ku(a){var b=Ld(a.elementId);!b&&a.j&&a.j.querySelector&&(b=a.j.querySelector("#"+a.elementId));return b}
function Mu(a){if(!a.h()){var b=Ku(a),c=!1;b&&b.getApiInterface&&b.getApiInterface()&&(c=!0);if(c){a.Y=!1;if(!Ou(a,"html5_remove_not_servable_check_killswitch")){var d;if((null==b?0:b.isNotServable)&&a.config&&(null==b?0:b.isNotServable(null==(d=a.config.args)?void 0:d.video_id)))return}Ru(a)}else a.lb=Ci(function(){Mu(a)},50)}}
function Ru(a){Cu(a);a.Ta=!0;var b=Ku(a);if(b){a.u=Su(a,b,"addEventListener");a.Da=Su(a,b,"removeEventListener");var c=b.getApiInterface();c=c.concat(b.getInternalApiInterface());for(var d=a.api,e=0;e<c.length;e++){var f=c[e];d[f]||(d[f]=Su(a,b,f))}}for(var g in a.i)a.i.hasOwnProperty(g)&&a.u&&a.u(g,a.i[g]);Gu(a);a.Ea&&a.Ea(a.api);a.T.ja("onReady",a.api)}
function Su(a,b,c){var d=b[c];return function(){var e=Ja.apply(0,arguments);try{return a.lastError=null,d.apply(b,e)}catch(f){"sendAbandonmentPing"!==c&&(f.params=c,a.lastError=f,Tp(f))}}}
function Cu(a){a.Ta=!1;if(a.Da)for(var b in a.i)a.i.hasOwnProperty(b)&&a.Da(b,a.i[b]);for(var c in a.L)a.L.hasOwnProperty(c)&&Di(Number(c));a.L={};a.u=null;a.Da=null;b=a.api;for(var d in b)b.hasOwnProperty(d)&&(b[d]=null);b.addEventListener=function(e,f){a.addEventListener(e,f)};
b.removeEventListener=function(e,f){a.removeEventListener(e,f)};
b.destroy=function(){a.dispose()};
b.getLastError=function(){return a.getLastError()};
b.getPlayerType=function(){return a.getPlayerType()};
b.getCurrentVideoConfig=function(){return a.Ua};
b.loadNewVideoConfig=function(e){a.loadNewVideoConfig(e)};
b.isReady=function(){return a.isReady()}}
l.isReady=function(){return this.Ta};
function Du(a){a.addEventListener("WATCH_LATER_VIDEO_ADDED",function(b){Un("WATCH_LATER_VIDEO_ADDED",b)});
a.addEventListener("WATCH_LATER_VIDEO_REMOVED",function(b){Un("WATCH_LATER_VIDEO_REMOVED",b)})}
l.addEventListener=function(a,b){var c=this,d=Iu(this,b);d&&(0<=fb(this.Mb,a)||this.i[a]||(b=Tu(this,a),this.u&&this.u(a,b)),this.T.subscribe(a,d),"onReady"===a&&this.isReady()&&Ci(function(){d(c.api)},0))};
l.removeEventListener=function(a,b){this.h()||(b=Iu(this,b))&&qg(this.T,a,b)};
function Iu(a,b){var c=b;if("string"===typeof b){if(a.Fa[b])return a.Fa[b];c=function(){var d=Ja.apply(0,arguments),e=z(b);if(e)try{e.apply(x,d)}catch(f){Sp(f)}};
a.Fa[b]=c}return c?c:null}
function Tu(a,b){var c="ytPlayer"+b+a.M;a.i[b]=c;x[c]=function(d){var e=Ci(function(){if(!a.h()){a.T.ja(b,null!=d?d:void 0);var f=a.L,g=String(e);g in f&&delete f[g]}},0);
tb(a.L,String(e))};
return c}
l.getPlayerType=function(){return this.fa||(Ku(this)?"html5":null)};
l.getLastError=function(){return this.lastError};
function Nu(a){a.cancel();Cu(a);a.fa=null;a.config&&(a.config.loaded=!1);var b=Ku(a);b&&(Ju(a)||!Qu(a)?a.l=b:(b&&b.destroy&&b.destroy(),a.l=null));if(a.m)for(a=a.m;b=a.firstChild;)a.removeChild(b)}
l.cancel=function(){this.A&&zt(Lu(this),this.A);Di(this.lb);this.Y=!1};
l.I=function(){Nu(this);if(this.l&&this.config&&this.l.destroy)try{this.l.destroy()}catch(b){Sp(b)}this.Fa=null;for(var a in this.i)this.i.hasOwnProperty(a)&&(x[this.i[a]]=null);this.Ua=this.config=this.api=null;delete this.m;delete this.j;K.prototype.I.call(this)};
function Qu(a){var b,c;a=null==(b=a.config)?void 0:null==(c=b.args)?void 0:c.fflags;return!!a&&-1!==a.indexOf("player_destroy_old_version=true")}
function Lu(a){return a.webPlayerContextConfig?a.webPlayerContextConfig.jsUrl:(a=a.config.assets)?a.js:""}
function Pu(a){return a.webPlayerContextConfig?a.webPlayerContextConfig.cssUrl:(a=a.config.assets)?a.css:""}
function Ou(a,b){if(a.webPlayerContextConfig)var c=a.webPlayerContextConfig.serializedExperimentFlags;else{var d;if(null==(d=a.config)?0:d.args)c=a.config.args.fflags}return"true"===pi(c||"","&")[b]}
function Hu(a){for(var b={},c=p(Object.keys(a)),d=c.next();!d.done;d=c.next()){d=d.value;var e=a[d];b[d]="object"===typeof e?wb(e):e}return b}
;var Uu={},Vu="player_uid_"+(1E9*Math.random()>>>0);function Wu(a,b,c){var d="player";c=void 0===c?!0:c;d="string"===typeof d?Ld(d):d;var e=Vu+"_"+Sa(d),f=Uu[e];if(f&&c)return Xu(a,b)?f.api.loadVideoByPlayerVars(a.args||null):f.loadNewVideoConfig(a),f.api;f=new Bu(d,e,a,b);Uu[e]=f;Un("player-added",f.api);re(f,function(){delete Uu[f.getId()]});
return f.api}
function Xu(a,b){return b&&b.serializedExperimentFlags?b.serializedExperimentFlags.includes("web_player_remove_playerproxy=true"):a&&a.args&&a.args.fflags?a.args.fflags.includes("web_player_remove_playerproxy=true"):!1}
;var Yu=null,Zu=null,$u=null;function av(){var a=Yu.getVideoData(1);a=a.title?a.title+" - YouTube":"YouTube";document.title!==a&&(document.title=a)}
;function bv(a,b,c){a="ST-"+ac(a).toString(36);b=b?hc(b):"";c=c||5;yq()&&oj(a,b,c)}
;function cv(a,b,c){b=void 0===b?{}:b;c=void 0===c?!1:c;var d=A("EVENT_ID");d&&(b.ei||(b.ei=d));if(b){d=a;var e=void 0===e?!0:e;var f=A("VALID_SESSION_TEMPDATA_DOMAINS",[]),g=ec(window.location.href);g&&f.push(g);g=ec(d);if(0<=fb(f,g)||!g&&0==d.lastIndexOf("/",0))if(M("autoescape_tempdata_url")&&(f=document.createElement("a"),Wb(f,d),d=f.href),d&&(d=fc(d),f=d.indexOf("#"),d=0>f?d:d.substr(0,f)))if(e&&!b.csn&&(b.itct||b.ved)&&(b=Object.assign({csn:kq()},b)),h){var h=parseInt(h,10);isFinite(h)&&0<h&&
bv(d,b,h)}else bv(d,b)}if(c)return!1;if((window.ytspf||{}).enabled)spf.navigate(a);else{var k=void 0===k?{}:k;var m=void 0===m?"":m;var q=void 0===q?window:q;c=q.location;a=ic(a,k)+m;var u=void 0===u?Wd:u;a:{u=void 0===u?Wd:u;for(k=0;k<u.length;++k)if(m=u[k],m instanceof Ud&&m.isValid(a)){u=new Fd(a,Dd);break a}u=void 0}c.href=Hd(u||Gd)}return!0}
;y("yt.setConfig",Zh,void 0);y("yt.config.set",Zh,void 0);y("yt.setMsg",pq,void 0);y("yt.msgs.set",pq,void 0);y("yt.logging.errors.log",Sp,void 0);
y("writeEmbed",function(){var a=A("PLAYER_CONFIG",void 0);if(!a){var b=A("PLAYER_VARS",void 0);b&&(a={args:b})}Gq(!0);"gvn"===a.args.ps&&(document.body.style.backgroundColor="transparent");a.attrs||(a.attrs={width:"100%",height:"100%",id:"video-player"});var c=document.referrer;b=A("POST_MESSAGE_ORIGIN");window!==window.top&&c&&c!==document.URL&&(a.args.loaderUrl=c);M("embeds_js_api_set_1p_cookie")&&(c=ui(window.location.href),c.embedsTokenValue&&(a.args.embedsTokenValue=c.embedsTokenValue));ds();
if((c=A("WEB_PLAYER_CONTEXT_CONFIGS",void 0))&&"WEB_PLAYER_CONTEXT_CONFIG_ID_EMBEDDED_PLAYER"in c){c=c.WEB_PLAYER_CONTEXT_CONFIG_ID_EMBEDDED_PLAYER;if(!c.serializedForcedExperimentIds){var d=ui(window.location.href);d.forced_experiments&&(c.serializedForcedExperimentIds=d.forced_experiments)}Yu=Wu(a,c,!1)}else Yu=Wu(a);Yu.addEventListener("onVideoDataChange",av);a=A("POST_MESSAGE_ID","player");A("ENABLE_JS_API")?$u=new lu(Yu):A("ENABLE_POST_API")&&"string"===typeof a&&"string"===typeof b&&(Zu=new su(window.parent,
a,b),$u=new pu(Yu,Zu.connection));Ct();M("ytidb_create_logger_embed_killswitch")||lk();M("flush_gel_on_teardown")&&(a={},Wt||(Wt=new Vt),Wt.install((a.flush_logs={ka:function(){$o()}},a)));
M("networkless_logging_web_embedded")&&(M("embeds_web_enable_new_nwl")?Xm():en());M("embeds_enable_ua_ch_polyfill")&&du();M("ytidb_clear_embedded_player")&&bf.N(function(){var e;if(!Ks){Qq||(Qq=new Nq);var f=Qq;var g={hc:Js,Kb:Is};f.providers.set(g.hc,g);g={ob:{feedbackEndpoint:ar(Es),modifyChannelNotificationPreferenceEndpoint:ar(Fs),playlistEditEndpoint:ar(Gs),subscribeEndpoint:ar(Cs),unsubscribeEndpoint:ar(Ds),webPlayerShareEntityServiceEndpoint:ar(Hs)}};var h=M("web_enable_client_location_service")?
Xq.getInstance():void 0,k={};h&&(k.client_location=h);if(void 0===m){Hq.h||(Hq.h=new Hq);var m=Hq.h}void 0===e&&(e=f.resolve(Js));rs(g,e,m,k);Ks=qs.h}lt()})},void 0);
var dv=hi(function(){is();var a=sj.getInstance(),b=vj(119),c=1<window.devicePixelRatio;if(document.body&&Bf(document.body,"exp-invert-logo"))if(c&&!Bf(document.body,"inverted-hdpi")){var d=document.body;if(d.classList)d.classList.add("inverted-hdpi");else if(!Bf(d,"inverted-hdpi")){var e=zf(d);Af(d,e+(0<e.length?" inverted-hdpi":"inverted-hdpi"))}}else!c&&Bf(document.body,"inverted-hdpi")&&Cf();if(b!=c){b="f"+(Math.floor(119/31)+1);d=wj(b)||0;d=c?d|67108864:d&-67108865;0==d?delete rj[b]:(c=d.toString(16),
rj[b]=c.toString());c=!0;M("web_secure_pref_cookie_killswitch")&&(c=!1);b=a.h;d=[];for(var f in rj)d.push(f+"="+encodeURIComponent(String(rj[f])));oj(b,d.join("&"),63072E3,a.i,c)}Us.h||(Us.h=new Us);a=Us.h;f=16623;var g=void 0===g?{}:g;Object.values(qq).includes(f)||(Tp(new Q("createClientScreen() called with a non-page VE",f)),f=83769);g.isHistoryNavigation||a.h.push({rootVe:f,key:g.key||""});a.o=[];a.C=[];g.rb?Xs(a,f,g):Ys(a,f,g)}),ev=hi(function(){Yu&&Yu.sendAbandonmentPing&&Yu.sendAbandonmentPing();
A("PL_ATT")&&Kt.dispose();for(var a=bf,b=0,c=At.length;b<c;b++)a.U(At[b]);At.length=0;xt("//static.doubleclick.net/instream/ad_status.js");Bt=!1;Zh("DCLKSTAT",0);qe($u,Zu);Yu&&(Yu.removeEventListener("onVideoDataChange",av),Yu.destroy())});
window.addEventListener?(window.addEventListener("load",dv),M("embeds_web_enable_replace_unload_w_pagehide")?window.addEventListener("pagehide",ev):window.addEventListener("unload",ev)):window.attachEvent&&(window.attachEvent("onload",dv),window.attachEvent("onunload",ev));Za("yt.abuse.player.botguardInitialized",z("yt.abuse.player.botguardInitialized")||Lt);Za("yt.abuse.player.invokeBotguard",z("yt.abuse.player.invokeBotguard")||Mt);
Za("yt.abuse.dclkstatus.checkDclkStatus",z("yt.abuse.dclkstatus.checkDclkStatus")||Dt);Za("yt.player.exports.navigate",z("yt.player.exports.navigate")||cv);Za("yt.util.activity.init",z("yt.util.activity.init")||Jn);Za("yt.util.activity.getTimeSinceActive",z("yt.util.activity.getTimeSinceActive")||Mn);Za("yt.util.activity.setTimestamp",z("yt.util.activity.setTimestamp")||Kn);}).call(this);
