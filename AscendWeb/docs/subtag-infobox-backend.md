# SubTag InfoBox Backend Contract

This doc describes what the frontend `SubTags` InfoBox needs, what Ascend already provides, and what the Django backend should add to fully support sub-tag (knowledge point) details.

## Current Situation

Frontend path:
- `src/components/KnowledgeGraph/SubTags.tsx` (hover -> `setInfoBox`)
- `src/components/KnowledgeGraph/InfoBox.tsx` (render)

Current Ascend Django API endpoints (from `/home/kkkzbh/code/Ascend/src/django_api/urls.py`):
- `POST /api/mastery/knowledge-points`
- `POST /api/recommendations/bank`
- `POST /api/metrics/student`
- `POST /api/path/plan`

What is already usable today:
- SubTag `mastery` (aka `tagScore`) can be derived from `POST /api/mastery/knowledge-points`.

Default semantics required by this project:
- If there is no evidence/record for a knowledge point, return `mastery = 0` (not 0.5).

What is missing for the subtag InfoBox:
- Per-knowledge-point solved count (`acCount`) for the hovered knowledge point.
- Per-knowledge-point recommendation list that comes back as an empty list when there is no recommendation.
- Problem link (URL) resolution for recommended problems.

## Frontend Data Fields Needed

For a hovered sub-tag (knowledge point), the InfoBox needs:

- `tagName`: string (knowledge point name, Chinese, as in `knowledge_tree.yaml`)
- `tagScore`: number in [0, 1] (mastery)
- `acCount`: integer (number of solved problems related to this knowledge point)
- `recommendedProblems`: list
  - `id`: string (`problem_id`)
  - `title`: string
  - `difficulty`: number (1-5 preferred, or keep current float)
  - `tags`: string[] (knowledge points / tags shown in UI)
  - `link`: string (URL)

Important UI rules:
- When there are no recommendations, return an empty list `[]` (frontend must not use placeholders).

## Recommended Backend API (Add One Endpoint)

Add a single endpoint dedicated to subtag hover details.

### Endpoint

`POST /api/knowledge/tag-detail`

### Request

```json
{
  "student": "<student_id>",
  "knowledge_point": "数组",
  "top_k": 5,
  "include_links": true
}
```

Notes:
- `knowledge_point` should be the canonical knowledge point name used in `/home/kkkzbh/code/Ascend/config/knowledge_tree.yaml`.
- `top_k` controls recommendation size.

### Response

```json
{
  "student": "<student_id>",
  "knowledge_point": "数组",
  "mastery": 0.73,
  "solved": 12,
  "attempted": 18,
  "recommendations": [
    {
      "problem_id": "1234",
      "title": "...",
      "difficulty": 2,
      "knowledge_points": ["数组", "双指针"],
      "score": 0.81,
      "reason": "...",
      "url": "https://..." 
    }
  ]
}
```

If no recommendations:

```json
{
  "student": "<student_id>",
  "knowledge_point": "数组",
  "mastery": 0.73,
  "solved": 12,
  "attempted": 18,
  "recommendations": []
}
```

## How To Compute `solved` / `attempted` (Backend Implementation Hint)

In Ascend, `KnowledgePointsCalculator._calculate_kp_mastery()` already builds `kp_stats`:
- `attempted`: number of problems attempted for a KP
- `solved`: number of problems solved (AC) for a KP
- `total_attempts`: total submissions for a KP (optional)

Currently only mastery is returned. Extend the metric detail output to include these counts.

Suggested change:
- In `KnowledgePointsCalculator.calculate(..., include_details=True)` return:
  - `details.per_knowledge_point[kp] = { mastery, solved, attempted, total_attempts }`

Also ensure the aggregator default is aligned:
- `KnowledgeHierarchyAggregator.DEFAULT_MASTERY` should be `0.0` (currently it is 0.5).

Then `POST /api/knowledge/tag-detail` can reuse this data to fill `solved/attempted`.

## How To Generate Recommendations Per Knowledge Point

Use `BankProblemRecommender.recommend()` with `target_knowledge_points`.

For a non-leaf knowledge point:
- Expand to leaf descendants using `KnowledgeTreeValidator.get_leaf_descendants(kp)`.

Return the recommender result, but ensure:
- empty list `[]` when no recommendation
- stable schema (problem_id/title/difficulty/knowledge_points/score/reason)

## Problem URL Resolution (Second Django Project)

Since you have another Django project to map `problem_id` -> title/url/source, integrate it in one of two ways:

Option A (recommended): Ascend backend calls the mapping service
- Mapping service endpoint (example): `POST /api/problems/resolve`
- Request: `{ "ids": ["1234", "5678"] }`
- Response: `{ "items": [{ "id": "1234", "url": "https://...", "title": "..." }] }`
- Ascend merges `url` into each recommendation item.

Option B: Frontend calls mapping service separately
- Ascend returns recommendations without `url`
- Frontend does a second request to resolve URLs

Given your request, prefer Option A so the frontend keeps a single hover-data request.

## Minimal Rollout Plan

Phase 1 (fast):
- Implement `POST /api/knowledge/tag-detail` with `mastery` + `solved` and `recommendations` (no `url` yet).

Phase 2:
- Add URL resolution via the mapping Django service.
