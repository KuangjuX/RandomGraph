echo "Running perf tests"
echo "=================="
echo "Perf T0=1000: "
make example EXAMPLE=perf T0=1000
echo "Perf T0=10000: "
make example EXAMPLE=perf T0=10000
echo "Perf T0=100000: "
make example EXAMPLE=perf T0=100000