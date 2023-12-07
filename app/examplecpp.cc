#include <example/example.hh>
#include <cstdlib>

#if EXAMPLE_ENABLE_MPI
#include <mpi.h>
#define EXIT(rc) MPI_Abort(MPI_COMM_WORLD, rc);
#define LOG(level, ...) do { if (rank == 0) log::level(__VA_ARGS__); } while (0)
#else
#define EXIT(rc) return rc;
#define LOG(level, ...) do { log::level(__VA_ARGS__); } while (0)
#endif

#define LOG_INFO(...) LOG(info, __VA_ARGS__)
#define LOG_ERROR(...) LOG(error, __VA_ARGS__)

int main(int argc, char *argv[]) {
  using namespace example;

#if EXAMPLE_ENABLE_MPI
  MPI_Init(&argc, &argv);

  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  LOG_INFO("MPI enabled: rank={} size={}", rank, size);
#endif

  std::string s;
  fmt::format_to(std::back_inserter(s), "{}", argv[0]);
  for (int i=1; i<argc; i++) {
    fmt::format_to(std::back_inserter(s), " {}", argv[i]);
  }
  LOG_INFO("{}\n", s);

#if EXAMPLE_ENABLE_MPI
  MPI_Finalize();
#endif

  return 0;
}
