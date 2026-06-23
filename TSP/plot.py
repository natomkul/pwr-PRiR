import pandas as pd
import matplotlib.pyplot as plt


def make_plot(results_csv, speedup_csv, plot_png, title):
    data = pd.read_csv(results_csv)
    data = data.sort_values("processes")

    t1 = data.loc[data["processes"] == 1, "time"].values[0]
    data["speedup"] = t1 / data["time"]

    print(data)

    data.to_csv(speedup_csv, index=False)

    plt.figure(figsize=(8, 6))
    plt.plot(data["processes"], data["speedup"], marker="o", label="zmierzone")
    plt.plot(data["processes"], data["processes"], linestyle="--", label="idealne (liniowe)")
    plt.xlabel("liczba procesow")
    plt.ylabel("przyspieszenie")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(plot_png, dpi=300, bbox_inches="tight")
    plt.close()


make_plot("csv/results_kroA100.csv", "csv/speedup_kroA100.csv", "wykresy/speedup_kroA100.png", "Przyspieszenie empiryczne vs liczba procesow (kroA100)")
make_plot("csv/results_kroA150.csv", "csv/speedup_kroA150.csv", "wykresy/speedup_kroA150.png", "Przyspieszenie empiryczne vs liczba procesow (kroA150)")
make_plot("csv/results_kroA200.csv", "csv/speedup_kroA200.csv", "wykresy/speedup_kroA200.png", "Przyspieszenie empiryczne vs liczba procesow (kroA200)")
