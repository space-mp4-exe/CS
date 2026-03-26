from itertools import product

# Work in F_3 = {0, 1, 2}
p = 3

def poly_eval(coeffs, x):
    """Evaluate polynomial with coeffs [a0, a1, ..., an] (ascending degree) at x mod p"""
    return sum(c * pow(x, i, p) for i, c in enumerate(coeffs)) % p

def poly_mul(f, g):
    """Multiply two polynomials over F_3 (coeffs in ascending degree order)"""
    result = [0] * (len(f) + len(g) - 1)
    for i, a in enumerate(f):
        for j, b in enumerate(g):
            result[i+j] = (result[i+j] + a * b) % p
    return result

def poly_mod(f, g):
    """Compute f mod g over F_3 (coeffs in DESCENDING degree order for division)"""
    f = list(f)
    g = list(g)
    while len(f) >= len(g):
        if f[0] == 0:
            f.pop(0)
            continue
        # leading coefficient of g is 1 (monic), so ratio = f[0]
        ratio = f[0]
        for i in range(len(g)):
            f[i] = (f[i] - ratio * g[i]) % p
        f.pop(0)
    # remove leading zeros
    while len(f) > 1 and f[0] == 0:
        f.pop(0)
    return f

def is_zero_poly(f):
    return all(c == 0 for c in f)

def poly_to_str(coeffs_asc, var='x', degree=4):
    """Pretty print polynomial from ascending-degree coefficients"""
    terms = []
    for i in range(len(coeffs_asc)-1, -1, -1):
        c = coeffs_asc[i]
        if c == 0:
            continue
        if i == 0:
            terms.append(str(c))
        elif i == 1:
            terms.append(f"{var}" if c == 1 else f"{c}{var}")
        else:
            terms.append(f"{var}^{i}" if c == 1 else f"{c}{var}^{i}")
    return " + ".join(terms) if terms else "0"

# All monic irreducible polynomials of degree 1, 2, 3 over F_3
def find_irreducibles(deg):
    irred = []
    for coeffs in product(range(p), repeat=deg):
        # monic: leading coeff = 1, so full poly is (1, *coeffs) descending = coeffs + [1] ascending... 
        # Let's store as ascending: coeffs[0]=const, ..., coeffs[deg-1]=x^(deg-1), leading=1
        poly_asc = list(coeffs) + [1]  # ascending, monic
        
        # Check no roots
        has_root = any(poly_eval(poly_asc, x) == 0 for x in range(p))
        if deg == 1:
            irred.append(poly_asc)
            continue
        if has_root:
            continue
        if deg == 2:
            irred.append(poly_asc)
            continue
        # For degree 3: no roots is sufficient for irreducibility
        if deg == 3:
            irred.append(poly_asc)
    return irred

irred1 = find_irreducibles(1)
irred2 = find_irreducibles(2)
irred3 = find_irreducibles(3)

print(f"Irreducible degree-1 polys: {len(irred1)}")
print(f"Irreducible degree-2 polys: {len(irred2)}")
for p2 in irred2:
    print(f"  {poly_to_str(p2)}")
print(f"Irreducible degree-3 polys: {len(irred3)}")

def try_factor_quartic(poly_asc):
    """
    Try to factor a monic degree-4 poly over F_3.
    Returns a list of factors (as ascending-coeff lists) if reducible, else None.
    poly_asc: ascending coefficients, leading coeff = 1
    """
    # poly in descending for poly_mod
    poly_desc = list(reversed(poly_asc))
    
    # Check degree-1 factors (i.e., roots)
    for x in range(p):
        if poly_eval(poly_asc, x) == 0:
            # (x - x0) = x + (-x0 mod 3) is a factor
            factor = [(-x) % p, 1]  # ascending: const + x
            return f"has root x={x}", [factor]
    
    # Check degree-2 irreducible factors
    for q in irred2:
        q_desc = list(reversed(q))
        rem = poly_mod(poly_desc[:], q_desc[:])
        if is_zero_poly(rem):
            # q divides poly; find cofactor by polynomial long division
            # quotient will be degree 2
            return f"has irred quadratic factor [{poly_to_str(q)}]", [q]
    
    return None, None

print("\n" + "="*70)
print("MONIC QUARTICS OVER F_3 — CHECKING NECESSARY CONDITIONS + FACTORING")
print("="*70)

irreducible_list = []
reducible_count = 0

for coeffs in product(range(p), repeat=4):
    # poly = x^4 + a*x^3 + b*x^2 + c*x + d
    # ascending: [d, c, b, a, 1]
    d, c, b, a = coeffs
    poly_asc = [d, c, b, a, 1]
    
    # Necessary condition 1: f(0) != 0 => d != 0
    if d == 0:
        continue
    
    # Necessary condition 2: f(1) != 0
    if poly_eval(poly_asc, 1) == 0:
        continue
    
    # Necessary condition 3: f(2) != 0
    if poly_eval(poly_asc, 2) == 0:
        continue
    
    # Now try to factor
    reason, factors = try_factor_quartic(poly_asc)
    
    poly_str = poly_to_str(poly_asc)
    
    if reason:
        reducible_count += 1
    else:
        irreducible_list.append(poly_asc)

print(f"\nPolys passing necessary conditions: {reducible_count + len(irreducible_list)}")
print(f"  Reducible (have irred factor of deg 1 or 2): {reducible_count}")
print(f"  Irreducible: {len(irreducible_list)}")

print(f"\n{'='*70}")
print(f"ALL {len(irreducible_list)} MONIC IRREDUCIBLE QUARTICS OVER F_3:")
print(f"{'='*70}")
for i, poly in enumerate(irreducible_list, 1):
    print(f"  {i:2d}. {poly_to_str(poly)}")

# Verification: double-check each is truly irreducible
print(f"\n{'='*70}")
print("VERIFICATION — confirming no factors of any degree:")
print(f"{'='*70}")
all_ok = True
for poly in irreducible_list:
    poly_str = poly_to_str(poly)
    # Check roots
    roots = [x for x in range(p) if poly_eval(poly, x) == 0]
    # Check irred quadratic factors
    quad_factors = []
    poly_desc = list(reversed(poly))
    for q in irred2:
        q_desc = list(reversed(q))
        rem = poly_mod(poly_desc[:], q_desc[:])
        if is_zero_poly(rem):
            quad_factors.append(poly_to_str(q))
    if roots or quad_factors:
        print(f"  ERROR: {poly_str} has factors! roots={roots}, quad={quad_factors}")
        all_ok = False

if all_ok:
    print(f"  All {len(irreducible_list)} polynomials confirmed irreducible. ✓")


# Also print the 6 reducible ones that passed necessary conditions (products of two irred quads)
print(f"\n{'='*70}")
print("THE 6 REDUCIBLE POLYS THAT PASSED THE ROOT TEST (products of irred quads):")
print(f"{'='*70}")
for coeffs in product(range(p), repeat=4):
    d, c, b, a = coeffs
    poly_asc = [d, c, b, a, 1]
    if d == 0: continue
    if poly_eval(poly_asc, 1) == 0: continue
    if poly_eval(poly_asc, 2) == 0: continue
    
    reason, factors = try_factor_quartic(poly_asc)
    if reason:
        poly_desc = list(reversed(poly_asc))
        # Find full factorization
        factorizations = []
        for q1 in irred2:
            q1_desc = list(reversed(q1))
            rem = poly_mod(poly_desc[:], q1_desc[:])
            if is_zero_poly(rem):
                # divide to get cofactor
                # polynomial long division
                quotient_desc = poly_desc[:]
                q1d = q1_desc[:]
                quot = []
                while len(quotient_desc) >= len(q1d):
                    ratio = quotient_desc[0]
                    quot.append(ratio)
                    for i in range(len(q1d)):
                        quotient_desc[i] = (quotient_desc[i] - ratio * q1d[i]) % p
                    quotient_desc.pop(0)
                quot_asc = list(reversed(quot))
                factorizations.append((q1, quot_asc))
        if factorizations:
            q1, q2 = factorizations[0]
            print(f"  {poly_to_str(poly_asc)} = ({poly_to_str(q1)})({poly_to_str(q2)})")
