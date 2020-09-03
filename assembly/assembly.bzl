def generate_assembly(name, srcs, deps=[]):
  architectures = [
      ('cascadelake', ''),
      ('cascadelake', 'prefer-512')
  ]
  for arch, modifier in architectures:
    tag = "%s-%s" % (name, arch)
    if modifier:
      tag += "-%s" % modifier
    copts = [
      "-march=%s" % arch,
      "-fno-math-errno",
      "-O3",
    ]
    if modifier == 'prefer-512':
      copts.append('-mprefer-vector-width=512')
    native.cc_library(
        name = tag,
        srcs = srcs,
        deps = deps,
        copts = copts,
        linkstatic = True,
    )
    native.genrule(
        name =  "%s-asm-gen" % tag,
        srcs = [
            ":%s" % tag,
        ],
        outs = [
            "%s.s" % tag,
        ],
        cmd = """
        objdump -S $(locations :%s) > $@
        """ % tag
    )
