#ifndef CLASS_STATS_H
#define CLASS_STATS_H

#include <common_stats.h>

#ifdef _MSC_VER
  #ifndef __unused
  #define __unused
  #endif
#else
  #ifndef __unused
  #define __unused __attribute__((__unused__))
  #endif
#endif

struct
{
  auto operator()(const float *TP, const float *FP, const int &Nclass)
  {
    std::unique_ptr<float[]> TOP(new float[Nclass]);
    std::transform(TP, TP + Nclass, FP, TOP.get(), [](const float &tp, const float fp){return tp + fp;});
    return TOP;
  }
} get_TOP;

struct
{
  auto operator()(const float *TN, const float *FN, const int &Nclass)
  {
    std::unique_ptr<float[]> TON(new float[Nclass]);
    std::transform(TN, TN + Nclass, FN, TON.get(), [](const float &tn, const float fn){return tn + fn;});
    return TON;
  }
} get_TON;

struct
{
  auto operator()(const float *TP, const float *FN, const int &Nclass)
  {
    std::unique_ptr<float[]> TPR(new float[Nclass]);
    std::transform(TP, TP + Nclass, FN, TPR.get(), [](const float &i1, const float &i2){return i1 / (i1 + i2);});
    return TPR;
  }
} get_TPR;

struct
{
  auto operator()(const float *TN, const float *FP, const int &Nclass)
  {
    std::unique_ptr<float[]> TNR(new float[Nclass]);
    std::transform(TN, TN + Nclass, FP, TNR.get(), [](const float &i1, const float &i2){return i1 / (i1 + i2);});
    return TNR;
  }
} get_TNR;

struct
{
  auto operator()(const float *TP, const float *FP, const int &Nclass)
  {
    std::unique_ptr<float[]> PPV(new float[Nclass]);
    std::transform(TP, TP + Nclass, FP, PPV.get(), [](const float &i1, const float &i2){return i1 / (i1 + i2);});
    return PPV;
  }
} get_PPV;

struct
{
  auto operator()(const float *TN, const float *FN, const int &Nclass)
  {
    std::unique_ptr<float[]> NPV(new float[Nclass]);
    std::transform(TN, TN + Nclass, FN, NPV.get(), [](const float &i1, const float &i2){return i1 / (i1 + i2);});
    return NPV;
  }
} get_NPV;

struct
{
  auto operator()(const float *TPR, const int &Nclass)
  {
    std::unique_ptr<float[]> FNR(new float[Nclass]);
    std::transform(TPR, TPR + Nclass, FNR.get(), [](const float &item){return 1.f - item;});
    return FNR;
  }
} get_FNR;

struct
{
  auto operator()(const float *TNR, const int &Nclass)
  {
    std::unique_ptr<float[]> FPR(new float[Nclass]);
    std::transform(TNR, TNR + Nclass, FPR.get(), [](const float &item){return 1.f - item;});
    return FPR;
  }
} get_FPR;

struct
{
  auto operator()(const float *PPV, const int &Nclass)
  {
    std::unique_ptr<float[]> FDR(new float[Nclass]);
    std::transform(PPV, PPV + Nclass, FDR.get(), [](const float &item){return 1.f - item;});
    return FDR;
  }
} get_FDR;

struct
{
  auto operator()(const float *NPV, const int &Nclass)
  {
    std::unique_ptr<float[]> FOR(new float[Nclass]);
    std::transform(NPV, NPV + Nclass, FOR.get(), [](const float &item){return 1.f - item;});
    return FOR;
  }
} get_FOR;

struct
{
  auto operator()(const float *TP, const float *FP, const float *FN, const float *TN, const int &Nclass)
  {
    std::unique_ptr<float[]> ACC(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      ACC[i] = ( TP[i] + TN[i] ) / (TP[i] + TN[i] + FN[i] + FP[i]);
    return ACC;
  }
} get_ACC;

struct
{
  auto operator()(const float *TP, const float *FP, const float *FN, const int &Nclass)
  {
    std::unique_ptr<float[]> F1_SCORE(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F1_SCORE[i] = (2.f * TP[i]) / (2.f * TP[i] + FP[i] + FN[i]);
    return F1_SCORE;
  }
} get_F1_SCORE;

struct
{
  auto operator()(const float *TP, const float *FP, const float *FN, const int &Nclass)
  {
    std::unique_ptr<float[]> F05_SCORE(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F05_SCORE[i] = (1.25f * TP[i]) / (1.25f * TP[i] + FP[i] + .25f * FN[i]);
    return F05_SCORE;
  }
} get_F05_SCORE;

struct
{
  auto operator()(const float *TP, const float *FP, const float *FN, const int &Nclass)
  {
    std::unique_ptr<float[]> F2_SCORE(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F2_SCORE[i] = (5.f * TP[i]) / (5.f * TP[i] + FP[i] + 4.f * FN[i]);
    return F2_SCORE;
  }
} get_F2_SCORE;

struct
{
  auto operator()(const float *TP, const float *TN, const float *FP, const float *FN, const int &Nclass)
  {
    std::unique_ptr<float[]> MCC(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      MCC[i] = (TP[i] * TN[i] - FP[i] * FN[i]) / (std::sqrt((TP[i] + FP[i])*(TP[i] + FN[i])*(TN[i] + FP[i])*(TN[i] + FN[i])));
    return MCC;
  }
} get_MCC;

struct
{
  auto operator()(const float *TPR, const float *TNR, const int &Nclass)
  {
    std::unique_ptr<float[]> BM(new float[Nclass]);
    std::transform(TPR, TPR + Nclass, TNR, BM.get(), [&](const float &tp, const float &tn){return tp + tn - 1.f;});
    return BM;
  }
} get_BM;

struct
{
  auto operator()(const float *PPV, const float *NPV, const int &Nclass)
  {
    std::unique_ptr<float[]> MK(new float[Nclass]);
    std::transform(PPV, PPV + Nclass, NPV, MK.get(), [&](const float &tp, const float &tn){return tp + tn - 1.f;});
    return MK;
  }
} get_MK;

struct
{
  auto operator()(const float *TPR, const float *FPR, const int &Nclass)
  {
    std::unique_ptr<float[]> PLR(new float[Nclass]);
    std::transform(TPR, TPR + Nclass, FPR, PLR.get(), [&](const float &tp, const float &tn){return tp / tn;});
    return PLR;
  }
} get_PLR;

struct
{
  auto operator()(const float *FNR, const float *TNR, const int &Nclass)
  {
    std::unique_ptr<float[]> NLR(new float[Nclass]);
    std::transform(FNR, FNR + Nclass, TNR, NLR.get(), [&](const float &tp, const float &tn){return tp / tn;});
    return NLR;
  }
} get_NLR;

struct
{
  auto operator()(const float *PLR, const float *NLR, const int &Nclass)
  {
    std::unique_ptr<float[]> DOR(new float[Nclass]);
    std::transform(PLR, PLR + Nclass, NLR, DOR.get(), [&](const float &tp, const float &tn){return tp / tn;});
    return DOR;
  }
} get_DOR;

struct
{
  auto operator()(const float *P, const float *POP, const int &Nclass)
  {
    std::unique_ptr<float[]> PRE(new float[Nclass]);
    std::transform(P, P + Nclass, POP, PRE.get(), [](const float &p, const float &pop){return p / pop;});
    return PRE;
  }
} get_PRE;

struct
{
  auto operator()(const float *PPV, const float *TPR, const int &Nclass)
  {
    std::unique_ptr<float[]> G(new float[Nclass]);
    std::transform(PPV, PPV + Nclass, TPR, G.get(), [](const float &i1, const float &i2){return std::sqrt(i1 * i2);});
    return G;
  }
} get_G;

struct
{
  auto operator()(const float *TOP, const float *P, const float *POP, const int &Nclass)
  {
    std::unique_ptr<float[]> RACC(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      RACC[i] = (TOP[i] * P[i]) / (POP[i] * POP[i]);
    return RACC;
  }
} get_RACC;

struct
{
  auto operator()(const float *ACC, const int &Nclass)
  {
    std::unique_ptr<float[]> ERR_ACC(new float[Nclass]);
    std::transform(ACC, ACC + Nclass, ERR_ACC.get(), [](const float &acc){return 1.f - acc;});
    return ERR_ACC;
  }
} get_ERR_ACC;

struct
{
  auto operator()(const float *TOP, const float *P, const float *POP, const int &Nclass)
  {
    std::unique_ptr<float[]> RACCU(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      RACCU[i] = (TOP[i] + P[i]) / (POP[i] * POP[i] * 4.f);
    return RACCU;
  }
} get_RACCU;

struct
{
  auto operator()(const float *TP, const float *TOP, const float *P, const int &Nclass)
  {
    std::unique_ptr<float[]> jaccard_index(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      jaccard_index[i] = TP[i] / (TOP[i] + P[i] - TP[i]);
    return jaccard_index;
  }
} get_jaccard_index;

struct
{
  auto operator()(const float *TP, const float *FP, const float *FN, const float *POP, const int &Nclass)
  {
    std::unique_ptr<float[]> IS(new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      IS[i] = -std::log2((TP[i] + FN[i]) / POP[i]) / (std::log2(TP[i] / (TP[i] + FP[i])));
    return IS;
  }
} get_IS;

struct
{
  auto operator()(__unused const float *classes, __unused const float *confusion_matrix, __unused const int &Nclass)
  {
    std::unique_ptr<float[]> CEN(new float[Nclass]);
    // MISS (modified = False)
    return CEN;
  }
} get_CEN;

struct
{
  auto operator()(__unused const float *classes, __unused const float *confusion_matrix, __unused const int &Nclass)
  {
    std::unique_ptr<float[]> MCEN(new float[Nclass]);
    // MISS (modified = True)
    return MCEN;
  }
} get_MCEN;

#endif // CLASS_STATS_H
