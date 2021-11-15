radius = 1E-4
ndim = 1
nball_volume = pi^(0.5*ndim)/gamma(0.5*ndim + 1)*radius^ndim

output = read.csv("output.csv")

# Compute crossing times/depths
subset = output[output$distance > radius, ]
result = tapply(subset$depth, subset$ns_run_id, max)
depth = mean(result)
h = -depth - log(nball_volume)
sem = sd(result) / sqrt(length(result))

cat("depth =", depth, "nats.\n")
cat("H(theta | d) =", h, "+-", sem, "nats.\n")
