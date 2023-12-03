#include <example/example.hh>

#ifdef EXAMPLE_ENABLE_MPI
#include <mpi.h>
#define EXIT(rc) MPI_Abort(MPI_COMM_WORLD, rc);
#else
#define EXIT(rc) return rc;
#endif

int main(int argc, char *argv[]) {

#ifdef EXAMPLE_ENABLE_MPI
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  if (rank == 0) { example::log::log("MPI enabled: rank={} size={}", rank, size); }
#endif

  std::string s;
  fmt::format_to(std::back_inserter(s), "{}", argv[0]);
  for (int i=1; i<argc; i++) {
    fmt::format_to(std::back_inserter(s), " {}", argv[i]);
  }
  example::log::log("{}", s);

#ifdef EXAMPLE_ENABLE_MPI
  MPI_Finalize();
#endif

  return 0;
}
