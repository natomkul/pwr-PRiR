import pandas as pd
import matplotlib.pyplot as plt

data = pd.read_csv("csv/results.csv")
data = data.sort_values("processes")

t1 = data.loc[data["processes"] == 1, "time"].values[0]
data["speedup"] = t1 / data["time"]

print(data)

data.to_csv("csv/speedup.csv", index=False)

plt.figure(figsize=(8, 6))
plt.plot(data["processes"], data["speedup"], marker="o", label="zmierzone")
plt.plot(data["processes"], data["processes"], linestyle="--", label="idealne (liniowe)")
plt.xlabel("liczba procesow")
plt.ylabel("przyspieszenie")
plt.title("Przyspieszenie empiryczne vs liczba procesow")
plt.legend()
plt.grid(True)
plt.savefig("wykresy/speedup.png", dpi=300, bbox_inches="tight")
plt.close()
