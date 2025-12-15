#ifndef TIMER_H
#define TIMER_H

typedef struct Timer {
    double remainingTime;
    double duration;
} Timer;

inline void InitTimer(Timer* timer, double duration) {
    *timer = (Timer) {
        .remainingTime = 0.0,
        .duration = duration
    };
}

inline void RestartTimer(Timer* timer) {
    timer -> remainingTime = timer -> duration;
}

inline bool IsTimeRemaining(Timer* timer) {
    return timer -> remainingTime > 0;
}

inline void DecrementTimer(Timer* timer, double elapsedTime) {
    if (!IsTimeRemaining(timer)) return;
    timer -> remainingTime -= elapsedTime;
}

typedef struct Stopwatch {
    double elapsedTime;
} Stopwatch;

inline void InitStopwatch(Stopwatch* stopwatch) {
    *stopwatch = (Stopwatch) {
        .elapsedTime = 0.0
    };
}

inline void ResetStopwatch(Stopwatch* stopwatch) {
    stopwatch -> elapsedTime = 0.0;
}

inline bool IsTimeElapsed(Stopwatch* stopwatch, double duration) {
    return stopwatch -> elapsedTime >= duration;
}

inline void IncrementStopwatch(Stopwatch* stopwatch, double elapsedTime) {
    stopwatch -> elapsedTime += elapsedTime;
}

#endif