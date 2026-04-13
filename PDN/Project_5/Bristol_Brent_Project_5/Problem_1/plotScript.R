# ── Load each CSV and add data_bytes (n_items × 4 bytes for int) ──────────────

diff_1M <- read.csv("time_1M_diff.csv")
diff_2M <- read.csv("time_2M_diff.csv")
diff_4M <- read.csv("time_4M_diff.csv")
diff_8M <- read.csv("time_8M_diff.csv")

same_1M <- read.csv("time_1M_same.csv")
same_2M <- read.csv("time_2M_same.csv")
same_4M <- read.csv("time_4M_same.csv")
same_8M <- read.csv("time_8M_same.csv")

# ── Combine and compute data_bytes ────────────────────────────────────────────

diff_data <- rbind(diff_1M, diff_2M, diff_4M, diff_8M)
same_data <- rbind(same_1M, same_2M, same_4M, same_8M)

diff_data$data_bytes <- diff_data$n_items * 4
same_data$data_bytes <- same_data$n_items * 4

# ── Linear regression ─────────────────────────────────────────────────────────

model_diff <- lm(avg_oneway_time ~ data_bytes, data = diff_data)
model_same <- lm(avg_oneway_time ~ data_bytes, data = same_data)

latency_diff   <- coef(model_diff)[1]
bandwidth_diff <- 1 / coef(model_diff)[2]

latency_same   <- coef(model_same)[1]
bandwidth_same <- 1 / coef(model_same)[2]

cat("=== Different Nodes ===\n")
cat(sprintf("Latency:   %.6f seconds\n", latency_diff))
cat(sprintf("Bandwidth: %.2f bytes/second\n", bandwidth_diff))

cat("\n=== Same Node ===\n")
cat(sprintf("Latency:   %.6f seconds\n", latency_same))
cat(sprintf("Bandwidth: %.2f bytes/second\n", bandwidth_same))

# ── Plot ──────────────────────────────────────────────────────────────────────

x_range  <- seq(min(c(diff_data$data_bytes, same_data$data_bytes)),
                max(c(diff_data$data_bytes, same_data$data_bytes)),
                length.out = 100)

diff_fit <- predict(model_diff, newdata = data.frame(data_bytes = x_range))
same_fit <- predict(model_same, newdata = data.frame(data_bytes = x_range))

plot(diff_data$data_bytes, diff_data$avg_oneway_time,
     col  = "blue", pch = 16,
     xlim = range(x_range),
     ylim = range(c(diff_data$avg_oneway_time, same_data$avg_oneway_time)),
     xlab = "Array Size (bytes)",
     ylab = "Avg One-Way Time (s)",
     main = "Ping-Pong Transmission Time with Line of Best Fit")

points(same_data$data_bytes, same_data$avg_oneway_time, col = "red", pch = 16)
lines(x_range, diff_fit, col = "blue", lwd = 2)
lines(x_range, same_fit, col = "red",  lwd = 2)

diff_eq <- sprintf("Diff Node: y = %.2e + %.2e x", coef(model_diff)[1], coef(model_diff)[2])
same_eq <- sprintf("Same Node: y = %.2e + %.2e x", coef(model_same)[1], coef(model_same)[2])

legend("topleft",
       legend = c(diff_eq, same_eq),
       col    = c("blue", "red"),
       lwd    = 2, pch = 16)

