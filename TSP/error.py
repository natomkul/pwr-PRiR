import pandas as pd
import matplotlib.pyplot as plt

best_known = {
    "kroA100": 21282,
    "kroA150": 26524,
    "kroA200": 29368,
}


def compute_error(results_csv, error_csv, optimal):
    data = pd.read_csv(results_csv)
    data = data.sort_values("processes")

    data["error_%"] = (data["length"] - optimal) / optimal * 100

    print(data)

    data.to_csv(error_csv, index=False)


def make_length_plot(results_csv, plot_png, title, optimal):
    data = pd.read_csv(results_csv)
    data = data.sort_values("processes")

    plt.figure(figsize=(8, 6))
    plt.plot(data["processes"], data["length"], marker="o", label="znalezione rozwiazanie")
    plt.axhline(y=optimal, color="r", linestyle="--", label="najlepsze znane rozwiazanie")
    plt.xlabel("liczba procesow")
    plt.ylabel("dlugosc trasy")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(plot_png, dpi=300, bbox_inches="tight")
    plt.close()


def make_time_plot(results_csv, plot_png, title):
    data = pd.read_csv(results_csv)
    data = data.sort_values("processes")

    plt.figure(figsize=(8, 6))
    plt.plot(data["processes"], data["time"], marker="o", label="zmierzony czas")
    plt.xlabel("liczba procesow")
    plt.ylabel("czas [s]")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(plot_png, dpi=300, bbox_inches="tight")
    plt.close()


for instance, optimal in best_known.items():
    results_csv = f"csv/results_{instance}.csv"

    compute_error(results_csv, f"csv/error_{instance}.csv", optimal)

    make_length_plot(results_csv, f"wykresy/length_{instance}.png",
                      f"Znalezione rozwiazanie vs najlepsze znane ({instance})", optimal)

    make_time_plot(results_csv, f"wykresy/time_{instance}.png",
                    f"Czas wykonania vs liczba procesow ({instance})")
