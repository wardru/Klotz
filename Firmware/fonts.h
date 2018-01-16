#ifndef FONT_H
#define FONT_H

 #define STA        0                                   // standart
 #define BIG        1                                    // big

 #define X_STA      7
 #define Y_STA      14
 #define X_BIG      27
 #define Y_BIG      34
 #define DOT_BIG    10

 #define ROW(X)     X * X_STA + 1
 #define LINE(Y)    Y * Y_STA + 1
 #define CX(X, Z)   X * Z + 1
 #define CY(Y, Z)   Y * Z + 1

extern const unsigned char char_0[197];
extern const unsigned char char_1[197];
extern const unsigned char char_2[197];
extern const unsigned char char_3[197];
extern const unsigned char char_4[197];
extern const unsigned char char_5[197];
extern const unsigned char char_6[197];
extern const unsigned char char_7[197];
extern const unsigned char char_8[197];
extern const unsigned char char_9[197];
extern const unsigned char char_a[197];
extern const unsigned char char_b[197];
extern const unsigned char char_c[197];
extern const unsigned char char_d[197];
extern const unsigned char char_e[197];
extern const unsigned char char_f[197];
extern const unsigned char char_g[197];
extern const unsigned char char_h[197];
extern const unsigned char char_i[197];
extern const unsigned char char_j[197];
extern const unsigned char char_k[197];
extern const unsigned char char_l[197];
extern const unsigned char char_m[197];
extern const unsigned char char_n[197];
extern const unsigned char char_o[197];
extern const unsigned char char_p[197];
extern const unsigned char char_q[197];
extern const unsigned char char_r[197];
extern const unsigned char char_s[197];
extern const unsigned char char_t[197];
extern const unsigned char char_u[197];
extern const unsigned char char_v[197];
extern const unsigned char char_w[197];
extern const unsigned char char_x[197];
extern const unsigned char char_y[197];
extern const unsigned char char_z[197];
extern const unsigned char char_A[197];
extern const unsigned char char_B[197];
extern const unsigned char char_C[197];
extern const unsigned char char_D[197];
extern const unsigned char char_E[197];
extern const unsigned char char_F[197];
extern const unsigned char char_G[197];
extern const unsigned char char_H[197];
extern const unsigned char char_I[197];
extern const unsigned char char_J[197];
extern const unsigned char char_K[197];
extern const unsigned char char_L[197];
extern const unsigned char char_M[197];
extern const unsigned char char_N[197];
extern const unsigned char char_O[197];
extern const unsigned char char_P[197];
extern const unsigned char char_Q[197];
extern const unsigned char char_R[197];
extern const unsigned char char_S[197];
extern const unsigned char char_T[197];
extern const unsigned char char_U[197];
extern const unsigned char char_V[197];
extern const unsigned char char_W[197];
extern const unsigned char char_X[197];
extern const unsigned char char_Y[197];
extern const unsigned char char_Z[197];
extern const unsigned char char_BIG_0[1837];
extern const unsigned char char_BIG_1[1837];
extern const unsigned char char_BIG_2[1837];
extern const unsigned char char_BIG_3[1837];
extern const unsigned char char_BIG_4[1837];
extern const unsigned char char_BIG_5[1837];
extern const unsigned char char_BIG_6[1837];
extern const unsigned char char_BIG_7[1837];
extern const unsigned char char_BIG_8[1837];
extern const unsigned char char_BIG_9[1837];
extern const unsigned char char_deg[32];

extern const unsigned char *alpha_l[26];
extern const unsigned char *alpha_n[10];
extern const unsigned char *alpha_N[10];
extern const unsigned char *alpha_L[26];

#endif