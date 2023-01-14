void calc_mesh_normals(vec3* normals, const vec3* verts, const int* faces, int nverts, int nfaces)
{
  for (int i = 0; i < nfaces; ++i) {
    int id1, id2, id3;

    // get vertex index
    id1 = faces[3 * i];
    id2 = faces[3 * i + 1];
    id3 = faces[3 * i + 2];

    // get normal
    vec3 n = cross(verts[id2] - verts[id1], verts[id3] - verts[id1]);

    // accumulate normals
    normals[id1] += n;
    normals[id2] += n;
    normals[id3] += n;
  }

  for (int i = 0; i < nverts; ++i) {
    normals[i] = normalize(normals[i]);
  }
}
