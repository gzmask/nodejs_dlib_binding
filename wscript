srcdir = "."
blddir = "build"
VERSION = "0.0.1"

def set_options(opt):
  opt.tool_options("compiler_cxx")

def configure(conf):
  conf.check_tool("compiler_cxx")
  conf.check_tool("node_addon")
  conf.env.append_value('LINKFLAGS', '-L/Users/ray/projects/nodejs_dlib_binding/smile')
  conf.env.append_value('LINKFLAGS', '-I/Users/ray/projects/nodejs_dlib_binding/smile')

def build(bld):
  obj = bld.new_task_gen("cxx", "shlib", "node_addon")
  # without this, eio_custom doesn't keep a ref to the req->data
  obj.cxxflags = ["-D_FILE_OFFSET_BITS=64", "-D_LARGEFILE_SOURCE", "-O3", "-DNDEBUG", "-ffast-math"]
  obj.target = "bayesian"
  obj.source = "bayesian_bind.cpp", "bayes_net.cpp"
  obj.lib = ["smile"]
