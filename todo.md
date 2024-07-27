#### Poser todo

Current todo (🔽 Priority):
- [ ] : pull in fstr, maybe rename to hstr?
- [ ] : put_f() for putting with a format
- [ ] : Nail down proper naming scheme, things are a bit fragmented atm
- [ ] : Cross platform cpu feature getting, AVX, etc.

---

#### 2024-07-27:
- [X] : Variadic args

Properly implemented varargs, va_init is pretty dope & convenient so that's
cool. Also added proper u64 to string support, it's kinda sketchy cuz im just
copying the i64 function but removed any negative related stuff, but I've had
no issues with it thus far.

---

#### 2024-07-26: 
Really bummed right now because apparently implementing my own
variadic args is not really a doable thing cross platform, apparently it's
mostly done compiler side, like my good friend `alloca(3)` (aka `salloc()`). So
I guess I'm just gonna use the compiler built in version which is kinda lame.
Also spent all day trying to get `___chkstk_ms()` working, but to no avail,
currently we're just rawdoggin stack allocations and letting stack overwrite
heap data, which is waver behavior. 


&emsp; Also on the topic of `salloc()` my current implementation just does a
call to compiler implemented `__builtin_alloca()` which is omoha. I tried
doing it with a variable length array of `u8`s which should work great, but
cuz `___chkstk_ms()` doesn't work properly it often segfaults because its
pissy about me modifying stack memory??? I remember being able to do this
safely but I guess not... maybe i gotta cast it to a `u8*` then modify that.


&emsp; I guess this is enough procrastination calculus, and I oughta get to
work on making sure variadic args will work.


---