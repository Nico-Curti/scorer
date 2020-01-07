#ifndef __class_stats_h__
#define __class_stats_h__

#include <common_stats.h>

struct // TOP(Test outcome positive)
{
  auto operator() (const float * TP, const float * FP, const int & Nclass)
  {
    std :: unique_ptr < float[] > TOP (new float[Nclass]);
    std :: transform(TP, TP + Nclass, FP, TOP.get(), [](const float & tp, const float & fp){return tp + fp;});
    return TOP;
  }
} get_TOP;

struct // TON(Test outcome negative)
{
  auto operator() (const float * TN, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > TON (new float[Nclass]);
    std :: transform(TN, TN + Nclass, FN, TON.get(), [](const float & tn, const float & fn){return tn + fn;});
    return TON;
  }
} get_TON;

struct // TPR(Sensitivity / recall / hit rate / true positive rate)
{
  auto operator() (const float * TP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > TPR (new float[Nclass]);
    std :: transform(TP, TP + Nclass, FN, TPR.get(), [](const float & i1, const float & i2){return i1 / (i1 + i2);});
    return TPR;
  }
} get_TPR;

struct // TNR(Specificity or true negative rate)
{
  auto operator() (const float * TN, const float * FP, const int & Nclass)
  {
    std :: unique_ptr < float[] > TNR (new float[Nclass]);
    std :: transform(TN, TN + Nclass, FP, TNR.get(), [](const float & i1, const float & i2){return i1 / (i1 + i2);});
    return TNR;
  }
} get_TNR;

struct // PPV(Precision or positive predictive value)
{
  auto operator() (const float * TP, const float * FP, const int & Nclass)
  {
    std :: unique_ptr < float[] > PPV (new float[Nclass]);
    std :: transform(TP, TP + Nclass, FP, PPV.get(), [](const float & i1, const float & i2){return i1 / (i1 + i2);});
    return PPV;
  }
} get_PPV;

struct // NPV(Negative predictive value)
{
  auto operator() (const float * TN, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > NPV (new float[Nclass]);
    std :: transform(TN, TN + Nclass, FN, NPV.get(), [](const float & i1, const float & i2){return i1 / (i1 + i2);});
    return NPV;
  }
} get_NPV;

struct // FNR(Miss rate or false negative rate)
{
  auto operator() (const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > FNR (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, FNR.get(), [](const float & item){return 1.f - item;});
    return FNR;
  }
} get_FNR;

struct // FPR(Fall-out or false positive rate)
{
  auto operator() (const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > FPR (new float[Nclass]);
    std :: transform(TNR, TNR + Nclass, FPR.get(), [](const float & item){return 1.f - item;});
    return FPR;
  }
} get_FPR;

struct // FDR(False discovery rate)
{
  auto operator() (const float * PPV, const int & Nclass)
  {
    std :: unique_ptr < float[] > FDR (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, FDR.get(), [](const float & item){return 1.f - item;});
    return FDR;
  }
} get_FDR;

struct // FOR(False omission rate)
{
  auto operator() (const float * NPV, const int & Nclass)
  {
    std :: unique_ptr < float[] > FOR (new float[Nclass]);
    std :: transform(NPV, NPV + Nclass, FOR.get(), [](const float & item){return 1.f - item;});
    return FOR;
  }
} get_FOR;

struct // ACC(Accuracy)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const float * TN, const int & Nclass)
  {
    std :: unique_ptr < float[] > ACC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      ACC[i] = ( TP[i] + TN[i] ) / (TP[i] + TN[i] + FN[i] + FP[i]);
    return ACC;
  }
} get_ACC;

struct // F1(F1 score - harmonic mean of precision and sensitivity)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > F1_SCORE (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F1_SCORE[i] = (2.f * TP[i]) / (2.f * TP[i] + FP[i] + FN[i]);
    return F1_SCORE;
  }
} get_F1_SCORE;

struct // F0.5(F0.5 score)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > F05_SCORE (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F05_SCORE[i] = (1.25f * TP[i]) / (1.25f * TP[i] + FP[i] + .25f * FN[i]);
    return F05_SCORE;
  }
} get_F05_SCORE;

struct // F2(F2 score)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > F2_SCORE (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      F2_SCORE[i] = (5.f * TP[i]) / (5.f * TP[i] + FP[i] + 4.f * FN[i]);
    return F2_SCORE;
  }
} get_F2_SCORE;

struct // MCC(Matthews correlation coefficient)
{
  auto operator() (const float * TP, const float * TN, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > MCC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      MCC[i] = (TP[i] * TN[i] - FP[i] * FN[i]) / (std :: sqrt( (TP[i] + FP[i]) * (TP[i] + FN[i]) * (TN[i] + FP[i]) * (TN[i] + FN[i]) ));
    return MCC;
  }
} get_MCC;

struct // BM(Informedness or bookmaker informedness)
{
  auto operator() (const float * TPR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > BM (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, TNR, BM.get(), [](const float & tp, const float & tn){return tp + tn - 1.f;});
    return BM;
  }
} get_BM;

struct // MK(Markedness)
{
  auto operator() (const float * PPV, const float * NPV, const int & Nclass)
  {
    std :: unique_ptr < float[] > MK (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, NPV, MK.get(), [](const float & tp, const float & tn){return tp + tn - 1.f;});
    return MK;
  }
} get_MK;

struct // ICSI(Individual classification success index)
{
  auto operator() (const float * PPV, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > ICSI (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, TPR, ICSI.get(), [](const float & tp, const float & tn){return tp + tn - 1.f;});
    return ICSI;
  }
} get_ICSI;

struct // PLR(Positive likelihood ratio)
{
  auto operator() (const float * TPR, const float * FPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > PLR (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, FPR, PLR.get(), [](const float & tp, const float & tn){return tp / tn;});
    return PLR;
  }
} get_PLR;

struct // NLR(Negative likelihood ratio)
{
  auto operator() (const float * FNR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > NLR (new float[Nclass]);
    std :: transform(FNR, FNR + Nclass, TNR, NLR.get(), [](const float & tp, const float & tn){return tp / tn;});
    return NLR;
  }
} get_NLR;

struct // DOR(Diagnostic odds ratio)
{
  auto operator() (const float * PLR, const float * NLR, const int & Nclass)
  {
    std :: unique_ptr < float[] > DOR (new float[Nclass]);
    std :: transform(PLR, PLR + Nclass, NLR, DOR.get(), [](const float & tp, const float & tn){return tp / tn;});
    return DOR;
  }
} get_DOR;

struct // PRE(Prevalence)
{
  auto operator() (const float * P, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > PRE (new float[Nclass]);
    std :: transform(P, P + Nclass, POP, PRE.get(), [](const float & p, const float & pop){return p / pop;});
    return PRE;
  }
} get_PRE;

struct // G(G-measure geometric mean of precision and sensitivity)
{
  auto operator() (const float * PPV, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > G (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, TPR, G.get(), [](const float & i1, const float & i2){return std :: sqrt(i1 * i2);});
    return G;
  }
} get_G;

struct // RACC(Random accuracy)
{
  auto operator() (const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > RACC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      RACC[i] = (TOP[i] * P[i]) / (POP[i] * POP[i]);
    return RACC;
  }
} get_RACC;

struct // ERR(Error rate)
{
  auto operator() (const float * ACC, const int & Nclass)
  {
    std :: unique_ptr < float[] > ERR_ACC (new float[Nclass]);
    std :: transform(ACC, ACC + Nclass, ERR_ACC.get(), [](const float & acc){return 1.f - acc;});
    return ERR_ACC;
  }
} get_ERR_ACC;

struct // RACCU(Random accuracy unbiased)
{
  auto operator() (const float * TOP, const float * P, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > RACCU (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      RACCU[i] = ( (TOP[i] + P[i]) * (TOP[i] + P[i]) ) / (POP[i] * POP[i] * 4.f);
    return RACCU;
  }
} get_RACCU;

struct // J(Jaccard index)
{
  auto operator() (const float * TP, const float * TOP, const float * P, const int & Nclass)
  {
    std :: unique_ptr < float[] > jaccard_index (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      jaccard_index[i] = TP[i] / (TOP[i] + P[i] - TP[i]);
    return jaccard_index;
  }
} get_jaccard_index;

struct // IS(Information score)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > IS (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      IS[i] = -std :: log2((TP[i] + FN[i]) / POP[i]) + (std :: log2(TP[i] / (TP[i] + FP[i])));
    return IS;
  }
} get_IS;

struct // CEN(Confusion entropy)
{
  auto operator() (const float * confusion_matrix, const int & Nclass)
  {
    std :: unique_ptr < float[] > CEN (new float[Nclass]);

    for (int i = 0; i < Nclass; ++i)
    {
      CEN[i] = 0.f;

      for (int j = 0; j < Nclass; ++j)
      {
        if (j != i)
        {
          float CEN_misclassification_calc = 0.f;

          for (int k = 0; k < Nclass; ++k)
            CEN_misclassification_calc += confusion_matrix[i * Nclass + k] + confusion_matrix[ k * Nclass + i];

          const float P_j_k = confusion_matrix[i * Nclass + j] / CEN_misclassification_calc;
          const float P_k_j = confusion_matrix[j * Nclass + i] / CEN_misclassification_calc;

          CEN[i] += P_j_k != 0.f ? P_j_k * (std :: log(P_j_k) / std :: log(2 * (Nclass - 1))) : 0.f;
          CEN[i] += P_k_j != 0.f ? P_k_j * (std :: log(P_k_j) / std :: log(2 * (Nclass - 1))) : 0.f;
        }
      }

      CEN[i] = -CEN[i];
    }

    return CEN;
  }
} get_CEN;

struct // MCEN(Modified confusion entropy)
{
  auto operator() (const float * confusion_matrix, const int & Nclass)
  {
    std :: unique_ptr < float[] > MCEN (new float[Nclass]);

    for (int i = 0; i < Nclass; ++i)
    {
      MCEN[i] = 0.f;

      for (int j = 0; j < Nclass; ++j)
      {
        if (j != i)
        {
          float CEN_misclassification_calc = 0.f;

          for (int k = 0; k < Nclass; ++k)
            CEN_misclassification_calc += confusion_matrix[i * Nclass + k] + confusion_matrix[ k * Nclass + i];

          CEN_misclassification_calc -= confusion_matrix[i * Nclass + i];

          const float P_j_k = confusion_matrix[i * Nclass + j] / CEN_misclassification_calc;
          const float P_k_j = confusion_matrix[j * Nclass + i] / CEN_misclassification_calc;

          MCEN[i] += P_j_k != 0.f ? P_j_k * (std :: log(P_j_k) / std :: log(2 * (Nclass - 1))) : 0.f;
          MCEN[i] += P_k_j != 0.f ? P_k_j * (std :: log(P_k_j) / std :: log(2 * (Nclass - 1))) : 0.f;
        }
      }

      MCEN[i] = -MCEN[i];
    }
    return MCEN;
  }
} get_MCEN;

struct // AUC(Area Under the ROC curve)
{
  auto operator() (const float * TNR, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > AUC (new float[Nclass]);
    std :: transform(TNR, TNR + Nclass, TPR, AUC.get(), [](const float & tnr, const float & tpr){return (tnr + tpr) * .5f;});
    return AUC;
  }

} get_AUC;

struct // dInd(Distance index)
{
  auto operator() (const float * TNR, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > dIND (new float[Nclass]);
    std :: transform(TNR, TNR + Nclass, TPR, dIND.get(), [](const float & tnr, const float & tpr){return std :: sqrt( (1.f - tnr) * (1.f - tnr) + (1.f - tpr) * (1.f - tpr) );});
    return dIND;
  }

} get_dIND;

struct // sInd(Similarity index)
{
  auto operator() (const float * dIND, const int & Nclass)
  {
    std :: unique_ptr < float[] > sIND (new float[Nclass]);
    std :: transform(dIND, dIND + Nclass, sIND.get(), [](const float & dind){return 1.f - (dind / std :: sqrt(2));});
    return sIND;
  }

} get_sIND;

struct // DP(Discriminant power)
{
  auto operator() (const float * TPR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > DP (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, TNR, DP.get(), [](const float & tpr, const float & tnr){return std :: sqrt(3) / 3.14f * (std :: log10(tpr / (1.f - tpr)) + std :: log10(tnr / (1.f - tnr)));});
    return DP;
  }

} get_DP;

struct // Y(Youden index)
{
  auto operator() (const float * BM, const int & Nclass)
  {
    std :: unique_ptr < float[] > Y (new float[Nclass]);
    std :: copy_n(BM, Nclass, Y.get());
    return Y;
  }

} get_Y;

struct // PLRI(Positive likelihood ratio interpretation)
{
  auto operator() (const float * PLR, const int & Nclass)
  {
    std :: unique_ptr < float[] > PLRI (new float[Nclass]);
    std :: transform(PLR, PLR + Nclass, PLRI.get(), [](const float & plr){return std :: isnan(plr) || std :: isinf(plr) ? -1.f : plr < 1.f ? 0.f : plr >= 1.f && plr < 5.f ? 1.f : plr >= 5.f && plr < 10.f ? 2.f : 3.f;});
    return PLRI;
  }

} get_PLRI;

struct // NLRI(Negative likelihood ratio interpretation)
{
  auto operator() (const float * NLR, const int & Nclass)
  {
    std :: unique_ptr < float[] > NLRI (new float[Nclass]);
    std :: transform(NLR, NLR + Nclass, NLRI.get(), [](const float & nlr){return std :: isnan(nlr) || std :: isinf(nlr) ? -1.f : nlr < .1f ? 0.f : nlr >= .1f && nlr < .2f ? 1.f : nlr >= .2f && nlr < .5f ? 2.f : 3.f;});
    return NLRI;
  }

} get_NLRI;

struct // DPI(Discriminant power interpretation)
{
  auto operator() (const float * DP, const int & Nclass)
  {
    std :: unique_ptr < float[] > DPI (new float[Nclass]);
    std :: transform(DP, DP + Nclass, DPI.get(), [](const float & dp){return std :: isnan(dp) || std :: isinf(dp) ? -1.f : dp < 1.f ? 0.f : dp >= 1.f && dp < 2.f ? 1.f : dp >= 2.f && dp < 3.f ? 2.f : 3.f;});
    return DPI;
  }

} get_DPI;

struct // AUCI(AUC value interpretation)
{
  auto operator() (const float * AUC, const int & Nclass)
  {
    std :: unique_ptr < float[] > AUCI (new float[Nclass]);
    std :: transform(AUC, AUC + Nclass, AUCI.get(), [](const float & auc){return std :: isnan(auc) || std :: isinf(auc) ? -1.f : auc < .6f ? 0.f : auc >= .6 && auc < .7f ? 1.f : auc >= .7f && auc < .8f ? 2.f : 3.f;});
    return AUCI;
  }

} get_AUCI;

struct // GI(Gini index)
{
  auto operator() (const float * AUC, const int & Nclass)
  {
    std :: unique_ptr < float[] > GI (new float[Nclass]);
    std :: transform(AUC, AUC + Nclass, GI.get(), [](const float & auc){return 2.f * auc - 1.f;});
    return GI;
  }

} get_GI;

struct // LS(Lift score)
{
  auto operator() (const float * PPV, const float * PRE, const int & Nclass)
  {
    std :: unique_ptr < float[] > LS (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, PRE, LS.get(), [](const float & ppv, const float & pre){return ppv / pre;});
    return LS;
  }

} get_LS;

struct // AM(Difference between automatic and manual classification)
{
  auto operator() (const float * TOP, const float * P, const int & Nclass)
  {
    std :: unique_ptr < float[] > AM (new float[Nclass]);
    std :: transform(TOP, TOP + Nclass, P, AM.get(), [](const float & top, const float & p){return top - p;});
    return AM;
  }

} get_AM;

struct // OP(Optimized precision)
{
  auto operator() (const float * ACC, const float * TPR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > OP (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
      OP[i] = ACC[i] - std :: fabs(TNR[i] - TPR[i]) / (TPR[i] + TNR[i]);

    return OP;
  }

} get_OP;

struct // IBA(Index of balanced accuracy)
{
  auto operator() (const float * TPR, const float * TNR, const int & Nclass)
  {
    std :: unique_ptr < float[] > IBA (new float[Nclass]);
    std :: transform(TPR, TPR + Nclass, TNR, IBA.get(), [](const float & tpr, const float & tnr){return (1.f + tpr - tnr) * tpr * tnr;});
    return IBA;
  }

} get_IBA;

struct // GM(G-mean geometric mean of specificity and sensitivity)
{
  auto operator() (const float * TNR, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > GM (new float[Nclass]);
    std :: transform(TNR, TNR + Nclass, TPR, GM.get(), [](const float & tnr, const float & tpr){return std :: sqrt(tnr * tpr);});
    return GM;
  }

} get_GM;

struct // Q(Yule Q - coefficient of colligation)
{
  auto operator() (const float * TP, const float * TN, const float * FP, const float * FN, const int & Nclass)
  {
    std :: unique_ptr < float[] > Q (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
    {
      const float OR = (TP[i] * TN[i]) / (FP[i] * FN[i]);
      Q[i] = (OR - 1.f) / (OR + 1.f);
    }
    return Q;
  }

} get_Q;

struct // AGM(Adjusted geometric mean)
{
  auto operator() (const float * TPR, const float * TNR, const float * GM, const float * N, const float * POP, const int & Nclass)
  {
    std :: unique_ptr < float[] > AGM (new float[Nclass]);

    for (int i = 0; i < Nclass; ++i)
    {
      if (POP[i] != 0.f)
      {
        AGM[i] = TPR[i] == 0.f ? 0.f : (GM[i] + TNR[i] * N[i] / POP[i]) / (1.f + N[i] / POP[i]);
      }
      else
        AGM[i] = -1.f;
    }

    return AGM;
  }

} get_AGM;

struct // MCCI(Matthews correlation coefficient interpretation)
{
  auto operator() (const float * MCC, const int & Nclass)
  {
    std :: unique_ptr < float[] > MCCI (new float[Nclass]);
    std :: transform(MCC, MCC + Nclass, MCCI.get(), [](const float & mcc){return std :: isnan(mcc) || std :: isinf(mcc) ? -1.f : mcc < .3f ? 0.f : mcc >= .3f && mcc < .5f ? 1.f : mcc >= .5f && mcc < .7f ? 2.f : mcc >= .7 && mcc < .9f ? 3.f : 4.f;});
    return MCCI;
  }

} get_MCCI;

struct // AGF(Adjusted F-score)
{
  auto operator() (const float * TP, const float * FP, const float * FN, const float * TN, const int & Nclass)
  {
    std :: unique_ptr < float[] > AGF (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
    {
      const float F2 = (5.f * TP[i]) / (5.f * TP[i] + FP[i] + 4.f * FN[i]);
      const float F05_inv = (1.25f * TN[i]) / (1.25f * TN[i] + FN[i] + .25f * FP[i]);
      AGF[i] = std :: sqrt(F2 * F05_inv);
    }

    return AGF;
  }

} get_AGF;

struct // OC(Overlap coefficient)
{
  auto operator() (const float * TP, const float * TOP, const float * P, const int & Nclass)
  {
    std :: unique_ptr < float[] > OC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
    {
      OC[i] = TP[i] / std :: min(TOP[i], P[i]);
    }

    return OC;
  }

} get_OC;

struct // OOC(Otsuka-Ochiai coefficient)
{
  auto operator() (const float * TP, const float * TOP, const float * P, const int & Nclass)
  {
    std :: unique_ptr < float[] > OOC (new float[Nclass]);
    for (int i = 0; i < Nclass; ++i)
    {
      OOC[i] = TP[i] / std :: sqrt(TOP[i] * P[i]);
    }

    return OOC;
  }

} get_OOC;

struct // AUPR(Area under the PR curve)
{
  auto operator() (const float * PPV, const float * TPR, const int & Nclass)
  {
    std :: unique_ptr < float[] > AUPR (new float[Nclass]);
    std :: transform(PPV, PPV + Nclass, TPR, AUPR.get(), [](const float & ppv, const float & tpr){return (ppv + tpr) * .5f;});

    return AUPR;
  }

} get_AUPR;

struct // BCD(Bray-Curtis dissimilarity)
{
  auto operator() (const float * TOP, const float * P, const float * AM, const int & Nclass)
  {
    std :: unique_ptr < float[] > BCD (new float[Nclass]);
    const float s = std :: accumulate(TOP, TOP + Nclass, 0.f) + std :: accumulate(P, P + Nclass, 0.f);
    std :: transform(AM, AM + Nclass, BCD.get(), [&](const float & am){return std :: fabs(am) / s;});
    return BCD;
  }

} get_BCD;


#endif // __class_stats_h__
