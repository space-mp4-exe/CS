#from sage.rings.integer_classes import is_prime_power

def find_irreducible(n, m, primitive=False, verbose=False):
    """
    Find an irreducible polynomial of degree m over F_n.

    Parameters:
        n        -- prime (or prime power) — the field size for the base field
        m        -- positive integer — desired degree
        primitive -- if True, find a *primitive* polynomial (so that x generates
                     the multiplicative group of F_{n^m})
        verbose  -- print step-by-step information

    Returns:
        A monic irreducible (or primitive) polynomial in F_n[x] of degree m.
    """
    # ── Validate inputs ──────────────────────────────────────────────────
    if not is_prime_power(n):
        raise ValueError(f"{n} is not a prime power — F_{n} does not exist.")
    if m < 1:
        raise ValueError(f"Degree m must be a positive integer, got {m}.")

    # ── Set up the base field and polynomial ring ────────────────────────
    F = GF(n)
    R.<x> = PolynomialRing(F)

    field_size  = n^m
    group_order = field_size - 1
    mode        = "primitive" if primitive else "irreducible"

    if verbose:
        print("=" * 60)
        print(f"  Searching for a monic {mode} polynomial")
        print(f"  over F_{n} of degree {m}")
        print("=" * 60)
        print(f"  Base field  : F_{n}")
        print(f"  Extension   : F_{n^m}  ({field_size} elements)")
        print(f"  Group order : {group_order} = {factor(group_order)}")
        print()

    # ── Primitive polynomial requires knowing prime factors of group order ─
    if primitive:
        prime_factors = [q for q, _ in factor(group_order)]
        if verbose:
            print(f"  Prime factors of {group_order}: {prime_factors}")
            print(f"  (will check x^(ord/q) ≠ 1 for each q)")
            print()

    def is_primitive(f):
        """Check if x is a primitive element mod f, i.e. ord(x mod f) = n^m - 1."""
        # First confirm f is irreducible
        if not f.is_irreducible():
            return False
        # x as an element of the quotient ring
        # Check x^(group_order) = 1 (should always hold if f irred — sanity check)
        # Check x^(group_order/q) ≠ 1 for all prime q | group_order
        for q in prime_factors:
            if pow(x, group_order // q, f) == 1:
                return False
        return True

    # ── Search strategy ──────────────────────────────────────────────────
    # 1. Try x itself (works when the Conway polynomial is degree m).
    # 2. Try small sparse polynomials (trinomials, pentanomials — fast for F_2).
    # 3. Fall back to random search.

    candidates_tried = 0

    def check(f):
        nonlocal candidates_tried
        candidates_tried += 1
        if primitive:
            return is_primitive(f)
        else:
            return f.is_irreducible()

    # Strategy 1: Sage's built-in — fastest when available
    if verbose:
        print("  [Strategy 1] Trying Sage's built-in random_irreducible_polynomial ...")
    try:
        # R.irreducible_element() returns a monic irreducible of given degree
        builtin = R.irreducible_element(m)
        candidates_tried += 1
        if verbose:
            print(f"  Found via built-in after {candidates_tried} attempt(s).\n")
        return builtin
    except Exception as e:
        if verbose:
            print(f"  Built-in unavailable ({e}). Falling back to manual search.\n")

    # Strategy 2: Sparse trinomials / pentanomials (important for F_2)
    if verbose:
        print("  [Strategy 2] Trying sparse polynomials (trinomials, pentanomials) ...")
    for k in range(1, m):
        f = x^m + x^k + F(1)
        if check(f):
            if verbose:
                print(f"  Found trinomial x^{m} + x^{k} + 1 "
                      f"after {candidates_tried} attempt(s).\n")
            return f

    if m >= 4:
        for a in range(1, m):
            for b in range(1, a):
                for c in range(1, b):
                    f = x^m + x^a + x^b + x^c + F(1)
                    if check(f):
                        if verbose:
                            print(f"  Found pentanomial x^{m}+x^{a}+x^{b}+x^{c}+1 "
                                  f"after {candidates_tried} attempt(s).\n")
                        return f

    # Strategy 3: Random search over all monic degree-m polynomials
    if verbose:
        print("  [Strategy 3] Random search ...")
    import random
    while True:
        coeffs = [F.random_element() for _ in range(m)] + [F(1)]
        f = R(coeffs)
        if check(f):
            if verbose:
                print(f"  Found after {candidates_tried} attempt(s).\n")
            return f


# ── Demo ─────────────────────────────────────────────────────────────────
if __name__ == "__main__":
    n = 2
    m = 283
    f = find_irreducible(n, m)
    #kind = "primitive" if prim else "irreducible"
    print(f"  f(x) = {f}")
    print(f"  → Monic irreducible polynomial of degree {m} over F_{n}.")
    print()